/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:43:04 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/17 16:36:56 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_error(t_parser *pars)
{
	if (!pars->current || pars->current->type == TOKEN_EOF)
		parse_error("syntax error near unexpected token `newline'");
	else if (pars->current->type == TOKEN_PIPE)
		parse_error("syntax error near unexpected token `|'");
	else if (pars->current->type == TOKEN_REDIR_APPEND)
		parse_error("syntax error near unexpected token `>>'");
	else if (pars->current->type == TOKEN_REDIR_OUT)
		parse_error("syntax error near unexpected token `>'");
	else if (pars->current->type == TOKEN_REDIR_IN)
		parse_error("syntax error near unexpected token `<'");
	else
		parse_error("syntax error near unexpected token");
	pars->error = 1;
}

static t_redir	*build_redir(t_parser *pars, t_token_type type)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
	{
		pars->error = 1;
		return (NULL);
	}
	redir->type = type;
	redir->file = ft_strdup(pars->current->value);
	if (!redir->file)
	{
		free(redir);
		pars->error = 1;
		return (NULL);
	}
	redir->quoted = pars->current->quoted;
	redir->ambiguous = 0;
	redir->heredoc_pipe = -1;
	return (redir);
}

void	add_redir(t_ast *node, t_parser *pars)
{
	t_redir			*redir;
	t_token_type	type;

	type = pars->current->type;
	next_token(pars);
	if (!pars->current || pars->current->type != TOKEN_WORD)
	{
		redir_error(pars);
		return ;
	}
	redir = build_redir(pars, type);
	if (!redir)
		return ;
	redir->next = node->redirs;
	node->redirs = redir;
	next_token(pars);
}

void	free_redir(t_redir *redir)
{
	t_redir	*to_free;

	while (redir)
	{
		to_free = redir;
		redir = redir->next;
		if (to_free->heredoc_pipe >= 0)
			close(to_free->heredoc_pipe);
		if (to_free->file)
			free(to_free->file);
		free(to_free);
	}
}
