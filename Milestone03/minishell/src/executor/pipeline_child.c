/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 01:36:19 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/18 01:36:20 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_other_heredoc_pipes(t_cmd *commands, t_cmd *skip)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = commands;
	while (cmd)
	{
		if (cmd != skip)
		{
			redir = cmd->redirections;
			while (redir)
			{
				if (redir->type == TOKEN_REDIR_HEREDOC
					&& redir->heredoc_pipe >= 0)
				{
					close(redir->heredoc_pipe);
					redir->heredoc_pipe = -1;
				}
				redir = redir->next;
			}
		}
		cmd = cmd->next;
	}
}

void	cleanup_pipes_and_exit(t_pipe_ctx *pipe_ctx,
				t_exec *exec_ctx, int code)
{
	if (pipe_ctx->pipes)
	{
		close_pipes(pipe_ctx->pipes, pipe_ctx->num_commands - 1);
		free_pipes(pipe_ctx->pipes, pipe_ctx->num_commands - 1);
	}
	cleanup_shell(exec_ctx);
	exit(code);
}

void	exec_cmd_child(t_cmd *cmd, t_exec *exec_ctx)
{
	char	*path;
	int		builtin_status;

	if (is_builtin(cmd->args[0]))
	{
		builtin_status = execute_builtin(cmd->args, exec_ctx);
		cleanup_shell(exec_ctx);
		exit(builtin_status);
	}
	path = resolve_cmd_path(cmd->args[0], exec_ctx);
	if (!path)
	{
		if (ft_strchr(cmd->args[0], '/'))
			error_msg("minishell", cmd->args[0], "No such file or directory");
		else
			error_msg(NULL, cmd->args[0], "command not found");
		cleanup_shell(exec_ctx);
		exit(EXIT_CMD_NOT_FOUND);
	}
	execve(path, cmd->args, exec_ctx->envp);
	handle_execve_error(path, cmd->args[0], exec_ctx);
}

static void	child_pipeline_cmd(t_cmd *commands, t_cmd *current,
				t_exec *exec_ctx, t_pipe_ctx *pipe_ctx)
{
	close_other_heredoc_pipes(commands, current);
	execute_pipeline_command(current, exec_ctx, pipe_ctx);
	exit(1);
}

pid_t	fork_one_cmd(t_cmd *commands, t_cmd *current,
				t_exec *exec_ctx, t_pipe_ctx *pipe_ctx)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		free(pipe_ctx->pids);
		pipe_ctx->pids = NULL;
		child_pipeline_cmd(commands, current, exec_ctx, pipe_ctx);
	}
	return (pid);
}
