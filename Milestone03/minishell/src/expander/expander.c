/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 18:18:22 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/17 14:06:05 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_all_quotes(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !(*in_double))
	{
		*in_single = !(*in_single);
		return (1);
	}
	if (c == '"' && !(*in_single))
	{
		*in_double = !(*in_double);
		return (1);
	}
	return (0);
}

static char	*expander_all_backslash(char *str, char *new_str, int *i)
{
	(*i)++;
	if (str[*i] == '"' || str[*i] == '$' || str[*i] == '\\')
		return (append_char_to_str(new_str, str[(*i)++]));
	new_str = append_char_to_str(new_str, '\\');
	if (new_str)
		new_str = append_char_to_str(new_str, str[(*i)++]);
	return (new_str);
}

char	*expander_all(char *str, t_exec *env)
{
	char	*new_str;
	int		i;
	int		in_single;
	int		in_double;

	new_str = ft_strdup("");
	if (!new_str)
		return (NULL);
	i = 0;
	in_double = 0;
	in_single = 0;
	while (str[i])
	{
		if (expand_all_quotes(str[i], &in_single, &in_double))
			i++;
		else if (str[i] == '\\' && in_double)
			new_str = expander_all_backslash(str, new_str, &i);
		else if (str[i] == '$' && !in_single)
			new_str = append_dollar_expansion(str, env, &i, new_str);
		else
			new_str = append_char_to_str(new_str, str[i++]);
		if (!new_str)
			return (NULL);
	}
	return (new_str);
}

int	expander(t_ast *node, t_exec *env)
{
	if (!node)
		return (0);
	if (node->args && expander_args(&node->args, node->args_quoted, env))
		return (1);
	if (node->redirs && expander_redirs(node->redirs, env))
		return (1);
	if (expander(node->left, env))
		return (1);
	if (expander(node->right, env))
		return (1);
	return (0);
}
