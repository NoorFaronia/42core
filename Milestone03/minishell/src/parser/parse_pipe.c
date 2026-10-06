/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:47:24 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/17 17:20:58 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->left = left;
	node->right = right;
	return (node);
}

static bool	match_token(t_parser *pars, t_token_type type)
{
	if (pars->current && pars->current->type == type)
	{
		next_token(pars);
		return (true);
	}
	return (false);
}

static int	pipe_error(t_parser *pars, t_ast *left)
{
	if (!pars->current || pars->current->type == TOKEN_EOF)
	{
		parse_error("syntax error near unexpected token `newline'");
		free_ast(left);
		return (0);
	}
	if (pars->current->type == TOKEN_PIPE)
	{
		parse_error("syntax error near unexpected token `|'");
		free_ast(left);
		return (0);
	}
	return (1);
}

t_ast	*parse_pipe(t_parser *pars)
{
	t_ast	*left;
	t_ast	*right;

	if (pars->current && pars->current->type == TOKEN_PIPE)
	{
		parse_error("syntax error near unexpected token `|'");
		return (NULL);
	}
	left = parse_cmd(pars);
	if (!left)
		return (NULL);
	while (match_token(pars, TOKEN_PIPE))
	{
		if (!pipe_error(pars, left))
			return (NULL);
		right = parse_cmd(pars);
		if (!right)
		{
			free_ast(left);
			return (NULL);
		}
		left = pipe_node(left, right);
	}
	return (left);
}
