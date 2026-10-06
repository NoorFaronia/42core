/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 07:23:41 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/11 02:24:30 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home(t_exec *exec_ctx, char *old_pwd)
{
	char	*home;
	int		i;

	i = find_env_var(exec_ctx->envp, "HOME");
	if (i == -1)
	{
		error_msg("cd", NULL, "HOME not set");
		free(old_pwd);
		return (NULL);
	}
	home = ft_strchr(exec_ctx->envp[i], '=');
	if (!home)
	{
		free(old_pwd);
		return (NULL);
	}
	return (ft_strdup(home + 1));
}

static char	*get_path(char **args, t_exec *exec_ctx, char *old_pwd)
{
	if (!args[1])
		return (get_home(exec_ctx, old_pwd));
	if (args[2])
	{
		error_msg("cd", NULL, "too many arguments");
		free(old_pwd);
		return (NULL);
	}
	return (args[1]);
}

static void	update_pwd_vars(char *old_pwd, t_exec *exec_ctx)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		set_env_var(&exec_ctx->envp, "PWD", new_pwd);
		free(new_pwd);
	}
	if (old_pwd)
	{
		set_env_var(&exec_ctx->envp, "OLDPWD", old_pwd);
		free(old_pwd);
	}
}

int	builtin_cd(char **args, t_exec *exec_ctx)
{
	char	*path;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	path = get_path(args, exec_ctx, old_pwd);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		error_msg("cd", path, strerror(errno));
		free(old_pwd);
		if (!args[1])
			free(path);
		return (1);
	}
	update_pwd_vars(old_pwd, exec_ctx);
	if (!args[1])
		free(path);
	return (0);
}
