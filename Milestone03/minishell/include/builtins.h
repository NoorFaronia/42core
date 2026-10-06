/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:29:33 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 13:04:57 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "executor.h"

// builtins.c
int		is_builtin(const char *cmd);
int		execute_builtin(char **args, t_exec *exec_ctx);

// cd.c
int		builtin_cd(char **args, t_exec *exec_ctx);

// echo.c
int		builtin_echo(char **args);

// env.c
int		builtin_env(char **args, t_exec *exec_ctx);

// pwd.c
int		builtin_pwd(void);

// export.c
int		builtin_export(char **args, t_exec *exec_ctx);

// env_utils.c
void	print_export_format(char **envp);
int		count_env_vars(char **envp);
char	**dup_env(char **envp);
int		find_env_var(char **envp, char *name);
char	*get_local_var_value(char **local_vars, char *name);

// env_modify.c
int		set_env_var(char ***envp, char *name, char *value);

// unset.c
int		builtin_unset(char **args, t_exec *exec_ctx);
int		unset_env_var(char ***envp, char *name);

// exit.c
int		builtin_exit(char **args, t_exec *exec_ctx);

#endif
