/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 18:18:22 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/21 19:24:15 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quoted_section(char **new_str, char *str,
			int *i, char delim)
{
	int		start;
	char	*new;
	char	*temp;

	start = ++(*i);
	while (str[*i] && str[*i] != delim)
		(*i)++;
	if (!str[*i])
		return ;
	new = ft_substr(str, start, *i - start);
	if (!new)
		return ;
	(*i)++;
	temp = ft_strjoin(*new_str, new);
	free(new);
	if (!temp)
		return ;
	free(*new_str);
	*new_str = temp;
}

char	*append_char_to_str(char *new_str, char c)
{
	char	ch[2];
	char	*temp;

	ch[0] = c;
	ch[1] = '\0';
	temp = ft_strjoin(new_str, ch);
	free(new_str);
	return (temp);
}

char	*expander_quotes(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = ft_strdup("");
	if (!new_str)
	{
		error_msg("Expander", NULL, "malloc error");
		return (NULL);
	}
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			handle_quoted_section(&new_str, str, &i, str[i]);
		else
		{
			new_str = append_char_to_str(new_str, str[i++]);
			if (!new_str)
				return (NULL);
		}
	}
	return (new_str);
}
