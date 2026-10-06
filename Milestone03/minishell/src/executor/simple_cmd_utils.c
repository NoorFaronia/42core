/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 01:37:01 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/18 01:37:02 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_stdio(int *saved_in, int *saved_out)
{
	*saved_in = dup(STDIN_FILENO);
	*saved_out = dup(STDOUT_FILENO);
	if (*saved_in == -1 || *saved_out == -1)
	{
		perror("dup");
		if (*saved_in != -1)
			close(*saved_in);
		if (*saved_out != -1)
			close(*saved_out);
		return (-1);
	}
	return (0);
}

void	restore_stdio(int saved_in, int saved_out)
{
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

int	get_exit_from_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

void	handle_execve_error(char *path, char *cmd_name, t_exec *exec_ctx)
{
	struct stat	st;
	int			exit_code;

	exit_code = EXIT_NOT_EXEC;
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		error_msg("minishell", cmd_name, "Is a directory");
	else if (errno == EACCES)
		error_msg("minishell", cmd_name, "Permission denied");
	else
	{
		perror("minishell");
		exit_code = EXIT_CMD_NOT_FOUND;
	}
	free(path);
	cleanup_shell(exec_ctx);
	exit(exit_code);
}
