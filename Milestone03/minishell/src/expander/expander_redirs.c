/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 18:18:22 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/17 14:18:52 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redir(t_redir *redir, t_exec *env)
{
	char	*exp;
	char	**split;

	exp = expander_all(redir->file, env);
	if (!exp)
		return (1);
	if (redir->quoted == NO_QUOTE)
	{
		split = ft_split(exp, ' ');
		if (!split || !split[0] || split[1])
		{
			redir->ambiguous = 1;
			free(exp);
			free_str_array(split);
			return (0);
		}
		free_str_array(split);
	}
	free(redir->file);
	redir->file = exp;
	redir->ambiguous = 0;
	return (0);
}

int	expander_redirs(t_redir *redir, t_exec *env)
{
	char	*exp;

	while (redir)
	{
		if (redir->type == TOKEN_REDIR_HEREDOC)
		{
			if (redir->quoted != NO_QUOTE)
			{
				exp = expander_quotes(redir->file);
				if (!exp)
					return (1);
				free(redir->file);
				redir->file = exp;
			}
		}
		else
		{
			if (handle_redir(redir, env))
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}
