/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 01:36:10 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/18 01:36:11 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_heredoc_lines(int write_fd, t_redir *redir, t_exec *exec_ctx)
{
	char	*delim;
	int		quoted;

	delim = redir->file;
	quoted = redir->quoted;
	while (!g_signal
		&& process_heredoc_line(write_fd, delim, quoted, exec_ctx) == 0)
		;
}

static int	process_one_heredoc(t_redir *current, t_exec *exec_ctx)
{
	int	pipe_fds[2];
	int	result;

	if (pipe(pipe_fds) < 0)
	{
		perror("pipe");
		return (-1);
	}
	result = fork_heredoc_reader(current, exec_ctx, pipe_fds);
	if (result < 0)
		return (result);
	current->heredoc_pipe = result;
	return (0);
}

static int	process_heredocs_loop(t_cmd *cmd, t_exec *exec_ctx)
{
	t_redir	*current;
	int		ret;

	current = cmd->redirections;
	while (current)
	{
		if (current->type == TOKEN_REDIR_HEREDOC)
		{
			ret = process_one_heredoc(current, exec_ctx);
			if (ret < 0)
			{
				if (ret == -2)
					exec_ctx->last_exit = EXIT_SIGINT;
				return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}

int	process_heredocs(t_cmd *cmd, t_exec *exec_ctx)
{
	struct sigaction	old_sa;
	struct sigaction	new_sa;
	int					ret;

	sigemptyset(&new_sa.sa_mask);
	new_sa.sa_flags = 0;
	new_sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &new_sa, &old_sa);
	ret = process_heredocs_loop(cmd, exec_ctx);
	sigaction(SIGINT, &old_sa, NULL);
	return (ret);
}
