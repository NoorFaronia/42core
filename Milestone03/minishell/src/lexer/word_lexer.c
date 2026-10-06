/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:49:05 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/21 19:18:39 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sep(char c)
{
	return (c == ' ' || c == '|'
		|| c == '\t' || c == '\n'
		|| c == '<' || c == '>');
}

static char	*plain(char *line, int *i)
{
	int		start;
	char	*part;

	start = *i;
	while (line[*i] && !sep(line[*i])
		&& line[*i] != '\'' && line[*i] != '"')
		(*i)++;
	part = ft_substr(line, start, *i - start);
	return (part);
}

static void	get_part(char **result, char *part)
{
	char	*temp;

	temp = ft_strjoin(*result, part);
	free(*result);
	free(part);
	if (!temp)
	{
		*result = NULL;
		return ;
	}
	*result = temp;
}

static char	*extract_part(char *line, int *i, int *quoted_flag)
{
	char	*part;

	if (line[*i] == '\'')
	{
		if (*quoted_flag == NO_QUOTE)
			*quoted_flag = SINGLE_QUOTE;
		if (!quote(&part, line, i))
			return (NULL);
	}
	else if (line[*i] == '"')
	{
		if (*quoted_flag == NO_QUOTE)
			*quoted_flag = DOUBLE_QUOTE;
		if (!quote(&part, line, i))
			return (NULL);
	}
	else
	{
		part = plain(line, i);
		if (!part)
			return (NULL);
	}
	return (part);
}

int	word(char *line, int *i, t_token **tokens)
{
	char	*tokens_word;
	char	*part;
	int		quoted_flag;

	tokens_word = ft_strdup("");
	if (!tokens_word)
		return (0);
	quoted_flag = NO_QUOTE;
	while (line[*i] && !sep(line[*i]))
	{
		part = extract_part(line, i, &quoted_flag);
		if (!part)
		{
			free(tokens_word);
			return (0);
		}
		get_part(&tokens_word, part);
	}
	add_token(tokens, TOKEN_WORD, tokens_word, quoted_flag);
	free(tokens_word);
	return (1);
}
