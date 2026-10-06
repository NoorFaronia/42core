/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:52:49 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/17 17:42:51 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "executor.h"
# include <stdbool.h>

// main_utils.c
int		init_exec(t_exec *exec_ctx, char **envp);
int		handle_input(char **input);
t_ast	*parse_input(char	*input, t_exec *exec_ctx);
void	process_line(char *input, t_exec *exec_ctx);

// prompt.c
char	*read_input(void);
bool	is_empty_input(const char *input);

/* history.c */
void	init_history(void);
void	add_to_history(const char *input);
void	save_history(void);
void	free_history(void);

// history_utils.c
void	load_history(void);

/* error_clean_utils.c */
void	error_msg(char *prefix, char *arg, char *msg);
void	cleanup_shell(t_exec *exec_ctx);
void	close_saved_stdio(t_exec *exec_ctx);
void	free_str_array(char **arr);

#endif
