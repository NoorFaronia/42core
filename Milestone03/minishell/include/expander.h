/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:37:29 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/17 14:25:32 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "executor.h"

// expander.c
char	*expander_all(char *str, t_exec *env);
int		expander(t_ast *node, t_exec *env);

// expander_quotes.c
char	*append_char_to_str(char *new_str, char c);
char	*expander_quotes(char *str);

// expander_variables.c
char	*append_dollar_expansion(char *str, t_exec *env, int *i, char *new_str);
char	*expander_variables(char *str, t_exec *env);

// expander_args.c
int		expander_args(char ***args, int *args_quoted, t_exec *env);

// expander_redirs.c
int		expander_redirs(t_redir *redir, t_exec *env);

#endif
