/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 01:36:55 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/18 01:36:56 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	apply_single_redir(t_redir *redir)
{
	if (redir->ambiguous)
	{
		error_msg("minishell", redir->file, "ambiguous redirect");
		return (-1);
	}
	if (redir->type == TOKEN_REDIR_IN)
		return (handle_input_redir(redir->file));
	else if (redir->type == TOKEN_REDIR_OUT)
		return (handle_output_redir(redir->file));
	else if (redir->type == TOKEN_REDIR_APPEND)
		return (handle_append_redir(redir->file));
	else if (redir->type == TOKEN_REDIR_HEREDOC)
		return (handle_heredoc(redir));
	return (0);
}

int	apply_redirections(t_redir *redirections, t_exec *exec_ctx)
{
	t_redir	*current;

	(void)exec_ctx;
	current = redirections;
	while (current)
	{
		if (apply_single_redir(current) < 0)
			return (-1);
		current = current->next;
	}
	return (0);
}
