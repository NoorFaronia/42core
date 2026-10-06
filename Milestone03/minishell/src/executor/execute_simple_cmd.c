/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 01:35:59 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/18 01:36:00 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_exec_process(char *path, t_cmd *cmd, t_exec *exec_ctx)
{
	restore_default_signals();
	close_saved_stdio(exec_ctx);
	execve(path, cmd->args, exec_ctx->envp);
	handle_execve_error(path, cmd->args[0], exec_ctx);
}

static int	fork_and_exec(t_cmd *cmd, char *path, t_exec *exec_ctx)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(path);
		return (1);
	}
	if (pid == 0)
		child_exec_process(path, cmd, exec_ctx);
	free(path);
	ignore_interactive_signals();
	waitpid(pid, &status, 0);
	setup_signals_shell();
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		else if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}
	return (get_exit_from_status(status));
}

int	run_external_cmd(t_cmd *cmd, t_exec *exec_ctx)
{
	char	*path;
	int		err;

	path = resolve_cmd_path(cmd->args[0], exec_ctx);
	if (!path)
	{
		if (ft_strchr(cmd->args[0], '/'))
		{
			err = errno;
			error_msg("minishell", cmd->args[0], strerror(err));
			if (err == ENOTDIR || err == EACCES)
				return (EXIT_NOT_EXEC);
			return (EXIT_CMD_NOT_FOUND);
		}
		error_msg("minishell", cmd->args[0], "command not found");
		return (EXIT_CMD_NOT_FOUND);
	}
	return (fork_and_exec(cmd, path, exec_ctx));
}

static int	setup_and_redir(t_cmd *cmd,
	t_exec *exec_ctx, int *saved_in, int *saved_out)
{
	if (process_heredocs(cmd, exec_ctx) < 0)
	{
		exec_ctx->last_exit = EXIT_SIGINT;
		return (EXIT_SIGINT);
	}
	if (save_stdio(saved_in, saved_out) < 0)
	{
		exec_ctx->last_exit = 1;
		return (1);
	}
	if (apply_redirections(cmd->redirections, exec_ctx) < 0)
	{
		restore_stdio(*saved_in, *saved_out);
		exec_ctx->last_exit = 1;
		return (1);
	}
	return (0);
}

int	execute_simple_cmd(t_cmd *cmd, t_exec *exec_ctx)
{
	int	saved_in;
	int	saved_out;
	int	status;

	if (!cmd)
		return (0);
	status = setup_and_redir(cmd, exec_ctx, &saved_in, &saved_out);
	if (status != 0)
		return (status);
	exec_ctx->saved_in = saved_in;
	exec_ctx->saved_out = saved_out;
	status = dispatch_cmd(cmd, exec_ctx);
	restore_stdio(saved_in, saved_out);
	exec_ctx->saved_in = -1;
	exec_ctx->saved_out = -1;
	exec_ctx->last_exit = status;
	return (status);
}
