/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:52:17 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/17 15:37:58 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*cmd_node(void)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_CMD;
	return (node);
}

static bool	is_redir_token(t_parser *pars)
{
	if (pars->current->type == TOKEN_REDIR_IN
		|| pars->current->type == TOKEN_REDIR_OUT
		|| pars->current->type == TOKEN_REDIR_APPEND
		|| pars->current->type == TOKEN_REDIR_HEREDOC)
		return (1);
	return (0);
}

void	next_token(t_parser *pars)
{
	if (pars->current)
		pars->current = pars->current->next;
}

t_ast	*parse_cmd(t_parser *pars)
{
	t_ast	*node;

	node = cmd_node();
	while (pars->current && pars->current->type != TOKEN_PIPE
		&& pars->current->type != TOKEN_EOF && !pars->error)
	{
		if (pars->current->type == TOKEN_WORD)
			add_arg(node, pars);
		else if (is_redir_token(pars))
			add_redir(node, pars);
		else
			break ;
	}
	if (pars->error)
	{
		free_ast(node);
		return (NULL);
	}
	if (!node->args && !node->redirs)
	{
		free(node->args_quoted);
		free(node);
		return (NULL);
	}
	return (node);
}
