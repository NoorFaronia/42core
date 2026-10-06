/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:43:04 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/17 16:53:18 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_args_array(char ***arr, char *str)
{
	int		len;
	char	**new_arr;

	len = 0;
	while (*arr && (*arr)[len])
		len++;
	new_arr = malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return ;
	ft_memcpy(new_arr, *arr, sizeof(char *) * len);
	new_arr[len] = str;
	new_arr[len + 1] = NULL;
	free(*arr);
	*arr = new_arr;
}

static int	expand_quoted_array(t_ast *node, int **new_quoted, int len)
{
	int	i;

	*new_quoted = malloc(sizeof(int) * (len + 2));
	if (!*new_quoted)
		return (0);
	if (node->args_quoted)
		ft_memcpy(*new_quoted, node->args_quoted, sizeof(int) * len);
	else
	{
		i = 0;
		while (i < len)
			(*new_quoted)[i++] = NO_QUOTE;
	}
	return (1);
}

void	add_arg(t_ast *node, t_parser *pars)
{
	char	*arg_value;
	int		len;
	int		*new_quoted;

	arg_value = ft_strdup(pars->current->value);
	if (!arg_value)
	{
		pars->error = 1;
		return ;
	}
	len = count_args(node);
	if (!expand_quoted_array(node, &new_quoted, len))
	{
		free(arg_value);
		pars->error = 1;
		return ;
	}
	new_quoted[len] = pars->current->quoted;
	new_quoted[len + 1] = 0;
	free(node->args_quoted);
	node->args_quoted = new_quoted;
	expand_args_array(&node->args, arg_value);
	next_token(pars);
}
