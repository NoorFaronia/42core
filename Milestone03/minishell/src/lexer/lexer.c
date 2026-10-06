/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:49:05 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/21 19:23:29 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_input_redir(char *line, int *i, t_token **tokens)
{
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		add_token(tokens, TOKEN_REDIR_HEREDOC, "<<", 0);
		(*i) += 2;
	}
	else if (line[*i] == '<')
	{
		add_token(tokens, TOKEN_REDIR_IN, "<", 0);
		(*i)++;
	}
}

static void	parse_output_redir(char *line, int *i, t_token **tokens)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		add_token(tokens, TOKEN_REDIR_APPEND, ">>", 0);
		(*i) += 2;
	}
	else if (line[*i] == '>')
	{
		add_token(tokens, TOKEN_REDIR_OUT, ">", 0);
		(*i)++;
	}
}

static void	operator(char *line, int *i, t_token **tokens)
{
	if (line[*i] == '|')
	{
		add_token(tokens, TOKEN_PIPE, "|", 0);
		(*i)++;
	}
	else if (line[*i] == '<')
		parse_input_redir(line, i, tokens);
	else if (line[*i] == '>')
		parse_output_redir(line, i, tokens);
}

t_token	*lexer(char *line)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (!line[i])
			break ;
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			operator(line, &i, &tokens);
		else
		{
			if (!word(line, &i, &tokens))
			{
				free_tokens(tokens);
				return (NULL);
			}
		}
	}
	add_token(&tokens, TOKEN_EOF, NULL, 0);
	return (tokens);
}
