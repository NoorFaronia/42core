/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 23:40:39 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 12:53:05 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append(char **full, const char *suffix)
{
	char	*tmp;

	tmp = ft_strjoin(*full, suffix);
	free(*full);
	*full = tmp;
	return (*full == NULL);
}

void	error_msg(char *prefix, char *arg, char *msg)
{
	char	*full;

	full = ft_strdup("");
	if (!full)
		return ;
	if (prefix)
		if (append(&full, prefix) || append(&full, ": "))
			return ;
	if (arg)
		if (append(&full, arg) || append(&full, ": "))
			return ;
	if (msg)
		if (append(&full, msg))
			return ;
	if (append(&full, "\n"))
		return ;
	write(STDERR_FILENO, full, ft_strlen(full));
	free(full);
}

void	close_saved_stdio(t_exec *exec_ctx)
{
	if (exec_ctx->saved_in >= 0)
	{
		close(exec_ctx->saved_in);
		exec_ctx->saved_in = -1;
	}
	if (exec_ctx->saved_out >= 0)
	{
		close(exec_ctx->saved_out);
		exec_ctx->saved_out = -1;
	}
}

void	cleanup_shell(t_exec *exec_ctx)
{
	if (!exec_ctx)
		return ;
	close_saved_stdio(exec_ctx);
	if (exec_ctx->cmd_list)
	{
		free_cmd_list(exec_ctx->cmd_list);
		exec_ctx->cmd_list = NULL;
	}
	if (exec_ctx->envp)
	{
		free_str_array(exec_ctx->envp);
		exec_ctx->envp = NULL;
	}
	if (exec_ctx->local_vars)
	{
		free_str_array(exec_ctx->local_vars);
		exec_ctx->local_vars = NULL;
	}
	rl_clear_history();
	free_history();
}

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
