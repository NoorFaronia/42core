/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 01:35:59 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/18 01:36:00 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	apply_temp_assignments(char **args, int n, t_exec *exec_ctx)
{
	int		i;
	char	*equals;
	char	*name;
	char	*value;

	i = 0;
	while (i < n)
	{
		equals = ft_strchr(args[i], '=');
		name = ft_substr(args[i], 0, equals - args[i]);
		value = ft_strdup(equals + 1);
		if (name && value)
			set_env_var(&exec_ctx->envp, name, value);
		free(name);
		free(value);
		i++;
	}
}

static int	run_cmd(t_cmd *cmd, t_exec *exec_ctx)
{
	if (!cmd->args[0] || cmd->args[0][0] == '\0')
	{
		error_msg("minishell", cmd->args[0], "command not found");
		return (EXIT_CMD_NOT_FOUND);
	}
	if (is_builtin(cmd->args[0]))
		return (execute_builtin(cmd->args, exec_ctx));
	return (run_external_cmd(cmd, exec_ctx));
}

static int	run_with_temp_env(t_cmd *cmd, t_exec *exec_ctx, int n_assigns)
{
	char	**old_envp;
	t_cmd	temp_cmd;
	int		result;

	old_envp = exec_ctx->envp;
	exec_ctx->envp = dup_env(old_envp);
	if (!exec_ctx->envp)
	{
		exec_ctx->envp = old_envp;
		return (1);
	}
	apply_temp_assignments(cmd->args, n_assigns, exec_ctx);
	temp_cmd.args = &cmd->args[n_assigns];
	temp_cmd.redirections = cmd->redirections;
	temp_cmd.next = NULL;
	result = run_cmd(&temp_cmd, exec_ctx);
	free_str_array(exec_ctx->envp);
	exec_ctx->envp = old_envp;
	return (result);
}

static void	apply_local_assignments(char **args, int n, t_exec *exec_ctx)
{
	int		i;
	char	*equals;
	char	*name;
	char	*value;

	i = 0;
	while (i < n)
	{
		equals = ft_strchr(args[i], '=');
		if (!equals)
		{
			i++;
			continue ;
		}
		name = ft_substr(args[i], 0, equals - args[i]);
		value = ft_strdup(equals + 1);
		if (name && value)
			set_env_var(&exec_ctx->local_vars, name, value);
		free(name);
		free(value);
		i++;
	}
}

int	dispatch_cmd(t_cmd *cmd, t_exec *exec_ctx)
{
	int	n_assigns;

	if (!cmd->args || !cmd->args[0])
		return (0);
	n_assigns = count_leading_assignments(cmd->args);
	if (n_assigns == 0)
		return (run_cmd(cmd, exec_ctx));
	if (!cmd->args[n_assigns])
	{
		apply_local_assignments(cmd->args, n_assigns, exec_ctx);
		return (0);
	}
	return (run_with_temp_env(cmd, exec_ctx, n_assigns));
}
