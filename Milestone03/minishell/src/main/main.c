/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 07:21:15 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/17 17:42:03 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_exit(int status)
{
	if (status == 0)
	{
		if (isatty(STDIN_FILENO))
			printf("exit\n");
		return (1);
	}
	return (0);
}

static void	run_shell_loop(t_exec *exec_ctx)
{
	char	*input;
	int		status;

	while (1)
	{
		status = handle_input(&input);
		if (g_signal == SIGINT)
		{
			exec_ctx->last_exit = 130;
			g_signal = 0;
			if (status != 1)
			{
				free(input);
				input = NULL;
			}
		}
		if (check_exit(status))
			break ;
		if (status == 2)
			continue ;
		process_line(input, exec_ctx);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_exec	exec_ctx;

	(void)argc;
	(void)argv;
	if (!init_exec(&exec_ctx, envp))
		return (1);
	run_shell_loop(&exec_ctx);
	save_history();
	cleanup_shell(&exec_ctx);
	return (exec_ctx.last_exit);
}
