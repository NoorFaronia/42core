/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_exec_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 01:36:23 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/18 01:36:35 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_all_heredocs(t_cmd *commands, t_exec *exec_ctx)
{
	t_cmd	*current;

	current = commands;
	while (current)
	{
		if (process_heredocs(current, exec_ctx) < 0)
			return (-1);
		current = current->next;
	}
	return (0);
}

void	setup_pipe_redirections(int **pipes, int cmd_index, int num_commands)
{
	if (cmd_index == 0)
		dup2(pipes[0][1], STDOUT_FILENO);
	else if (cmd_index == num_commands - 1)
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	else
	{
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	}
}

void	execute_pipeline_command(t_cmd *cmd, t_exec *exec_ctx,
			t_pipe_ctx *pipe_ctx)
{
	if (pipe_ctx->pipes)
		setup_pipe_redirections(pipe_ctx->pipes,
			pipe_ctx->cmd_index, pipe_ctx->num_commands);
	if (apply_redirections(cmd->redirections, exec_ctx) < 0)
		cleanup_pipes_and_exit(pipe_ctx, exec_ctx, 1);
	if (pipe_ctx->pipes)
	{
		close_pipes(pipe_ctx->pipes, pipe_ctx->num_commands - 1);
		free_pipes(pipe_ctx->pipes, pipe_ctx->num_commands - 1);
	}
	restore_default_signals();
	exec_cmd_child(cmd, exec_ctx);
}
