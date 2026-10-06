/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 07:21:15 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/17 17:41:52 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_exec(t_exec *exec_ctx, char **envp)
{
	exec_ctx->envp = dup_env(envp);
	if (!exec_ctx->envp)
	{
		error_msg("Fatal", NULL, "failed to initialize environment");
		return (0);
	}
	exec_ctx->local_vars = malloc(sizeof(char *));
	if (!exec_ctx->local_vars)
	{
		free_str_array(exec_ctx->envp);
		return (0);
	}
	exec_ctx->local_vars[0] = NULL;
	exec_ctx->last_exit = 0;
	exec_ctx->cmd_list = NULL;
	exec_ctx->saved_in = -1;
	exec_ctx->saved_out = -1;
	setup_signals_shell();
	init_history();
	return (1);
}

int	handle_input(char **input)
{
	*input = read_input();
	if (!*input)
		return (0);
	if (is_empty_input(*input))
	{
		free(*input);
		*input = NULL;
		return (2);
	}
	if (isatty(STDIN_FILENO))
		add_to_history(*input);
	return (1);
}

t_ast	*parse_input(char	*input, t_exec *exec_ctx)
{
	t_token	*tokens;
	t_ast	*ast;

	tokens = lexer(input);
	free(input);
	if (!tokens)
	{
		exec_ctx->last_exit = 2;
		return (NULL);
	}
	ast = parser(tokens);
	free_tokens(tokens);
	if (!ast)
	{
		exec_ctx->last_exit = 2;
		return (NULL);
	}
	if (expander(ast, exec_ctx))
	{
		free_ast(ast);
		return (NULL);
	}
	return (ast);
}

void	process_line(char	*input, t_exec *exec_ctx)
{
	t_ast	*ast;
	t_cmd	*cmd_list;

	ast = parse_input(input, exec_ctx);
	if (!ast)
		return ;
	cmd_list = ast_to_cmd_list(ast);
	free_ast(ast);
	if (cmd_list)
	{
		exec_ctx->cmd_list = cmd_list;
		execute_pipeline(cmd_list, exec_ctx);
		exec_ctx->cmd_list = NULL;
	}
	free_cmd_list(cmd_list);
}
