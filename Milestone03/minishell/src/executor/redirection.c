/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 01:35:46 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/18 01:35:47 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_and_redirect(char *filename, int flags, int target_fd)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		error_msg("minishell", filename, strerror(errno));
		return (-1);
	}
	dup2(fd, target_fd);
	close(fd);
	return (0);
}

int	handle_input_redir(char *filename)
{
	return (open_and_redirect(filename, O_RDONLY, STDIN_FILENO));
}

int	handle_output_redir(char *filename)
{
	return (open_and_redirect(filename,
			O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO));
}

int	handle_append_redir(char *filename)
{
	return (open_and_redirect(filename,
			O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO));
}

int	handle_heredoc(t_redir *redir)
{
	dup2(redir->heredoc_pipe, STDIN_FILENO);
	close(redir->heredoc_pipe);
	redir->heredoc_pipe = -1;
	return (0);
}
