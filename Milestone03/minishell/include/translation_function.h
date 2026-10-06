/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_function.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:46:08 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/17 17:49:17 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSLATION_FUNCTION_H
# define TRANSLATION_FUNCTION_H

# include "executor.h"

t_cmd	*ast_to_cmd_list(t_ast *node);
void	free_cmd_list(t_cmd *cmd);
int		count_args(t_ast *node);

#endif
