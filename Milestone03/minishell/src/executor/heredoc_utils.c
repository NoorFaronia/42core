/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 01:35:29 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/18 01:35:30 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		g_hd_write_fd = -1;

static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	if (g_hd_write_fd >= 0)
	{
		close(g_hd_write_fd);
		g_hd_write_fd = -1;
	}
	close(STDIN_FILENO);
}

int	process_heredoc_line(int write_fd,
	char *delim, int quoted, t_exec *exec_ctx)
{
	char	*line;
	char	*expanded;

	line = readline("> ");
	if (!line)
		return (1);
	if (ft_strcmp(line, delim) == 0)
	{
		free(line);
		return (1);
	}
	if (quoted == NO_QUOTE)
		expanded = expander_variables(line, exec_ctx);
	else
		expanded = ft_strdup(line);
	free(line);
	if (!expanded)
		return (1);
	write(write_fd, expanded, ft_strlen(expanded));
	write(write_fd, "\n", 1);
	free(expanded);
	return (0);
}

static void	child_heredoc_reader(t_redir *redir,
	t_exec *exec_ctx, int *pipe_fds)
{
	signal(SIGQUIT, SIG_IGN);
	close(pipe_fds[0]);
	g_hd_write_fd = pipe_fds[1];
	g_signal = 0;
	signal(SIGINT, heredoc_sigint_handler);
	read_heredoc_lines(pipe_fds[1], redir, exec_ctx);
	g_hd_write_fd = -1;
	close(pipe_fds[1]);
	cleanup_shell(exec_ctx);
	if (g_signal)
		exit(130);
	else
		exit(0);
}

static int	parent_wait_for_heredoc(pid_t pid, int *pipe_fds)
{
	int	status;

	close(pipe_fds[1]);
	waitpid(pid, &status, 0);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		close(pipe_fds[0]);
		write(STDOUT_FILENO, "\n", 1);
		return (-2);
	}
	return (pipe_fds[0]);
}

int	fork_heredoc_reader(t_redir *redir, t_exec *exec_ctx, int *pipe_fds)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		return (-1);
	}
	if (pid == 0)
		child_heredoc_reader(redir, exec_ctx, pipe_fds);
	return (parent_wait_for_heredoc(pid, pipe_fds));
}
