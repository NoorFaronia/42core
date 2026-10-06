/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 01:36:13 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/18 01:36:14 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_full_path(char *dir, char *command)
{
	char	*slash;
	char	*full_path;

	slash = ft_strjoin(dir, "/");
	if (!slash)
		return (NULL);
	full_path = ft_strjoin(slash, command);
	free(slash);
	return (full_path);
}

static char	**get_paths_from_env(t_exec *exec_ctx)
{
	int		index;
	char	*path_env;
	char	**paths;

	index = find_env_var(exec_ctx->envp, "PATH");
	if (index == -1)
		return (NULL);
	path_env = ft_strchr(exec_ctx->envp[index], '=');
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env + 1, ':');
	return (paths);
}

static int	is_executable(char *path)
{
	return (access(path, F_OK) == 0 && access(path, X_OK) == 0);
}

static char	*find_command_in_path(char *command, t_exec *exec_ctx)
{
	char	**paths;
	char	*full_path;
	int		i;

	paths = get_paths_from_env(exec_ctx);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = build_full_path(paths[i], command);
		if (full_path && is_executable(full_path))
		{
			free_str_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_str_array(paths);
	return (NULL);
}

char	*resolve_cmd_path(char *command, t_exec *exec_ctx)
{
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
	return (find_command_in_path(command, exec_ctx));
}
