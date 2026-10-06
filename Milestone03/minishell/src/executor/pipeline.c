/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 01:36:49 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/18 01:36:50 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	*fork_pipeline_cmds(t_cmd *commands, t_exec *exec_ctx,
									int **pipes, int num_commands)
{
	pid_t		*pids;
	t_cmd		*current;
	t_pipe_ctx	pipe_ctx;

	pids = malloc(sizeof(pid_t) * num_commands);
	if (!pids)
		return (NULL);
	current = commands;
	pipe_ctx.pipes = pipes;
	pipe_ctx.num_commands = num_commands;
	pipe_ctx.cmd_index = 0;
	pipe_ctx.pids = pids;
	while (pipe_ctx.cmd_index < num_commands && current)
	{
		pids[pipe_ctx.cmd_index] = fork_one_cmd(commands, current,
				exec_ctx, &pipe_ctx);
		current = current->next;
		pipe_ctx.cmd_index++;
	}
	return (pids);
}

static int	wait_pipeline_cmds(pid_t *pids, int num_commands,
								t_exec *exec_ctx)
{
	int	status;
	int	sigint_received;
	int	sigquit_received;
	int	i;

	sigint_received = 0;
	sigquit_received = 0;
	status = 0;
	i = 0;
	while (i < num_commands)
	{
		waitpid(pids[i], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			sigint_received = 1;
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			sigquit_received = 1;
		i++;
	}
	setup_signals_shell();
	if (sigquit_received)
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	if (sigint_received)
		write(STDOUT_FILENO, "\n", 1);
	exec_ctx->last_exit = get_exit_from_status(status);
	return (exec_ctx->last_exit);
}

static int	run_pipeline(t_cmd *commands, t_exec *exec_ctx,
				int **pipes, int num_commands)
{
	pid_t	*pids;
	int		result;

	pids = fork_pipeline_cmds(commands, exec_ctx, pipes, num_commands);
	if (!pids)
	{
		close_pipes(pipes, num_commands - 1);
		free_pipes(pipes, num_commands - 1);
		return (1);
	}
	close_pipes(pipes, num_commands - 1);
	ignore_interactive_signals();
	result = wait_pipeline_cmds(pids, num_commands, exec_ctx);
	free_pipes(pipes, num_commands - 1);
	free(pids);
	return (result);
}

int	execute_pipeline(t_cmd *commands, t_exec *exec_ctx)
{
	int		num_commands;
	int		**pipes;

	if (!commands)
		return (1);
	num_commands = count_commands(commands);
	if (num_commands == 1)
		return (execute_simple_cmd(commands, exec_ctx));
	if (process_all_heredocs(commands, exec_ctx) < 0)
	{
		exec_ctx->last_exit = EXIT_SIGINT;
		return (EXIT_SIGINT);
	}
	pipes = create_pipes(num_commands - 1);
	if (!pipes)
		return (1);
	return (run_pipeline(commands, exec_ctx, pipes, num_commands));
}
