/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 05:51:06 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 12:06:24 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*g_builtins[] = {
	"exit", "echo", "cd", "pwd", "export", "unset", "env", NULL
};

int	is_builtin(const char *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	while (g_builtins[i])
	{
		if (ft_strcmp(cmd, g_builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	execute_builtin(char **args, t_exec *exec_ctx)
{
	if (!args || !args[0])
		return (0);
	if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args, exec_ctx));
	if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(args, exec_ctx));
	if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, exec_ctx));
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, exec_ctx));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, exec_ctx));
	return (0);
}
