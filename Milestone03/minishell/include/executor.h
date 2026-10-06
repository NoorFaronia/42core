/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 02:03:16 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 12:22:13 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <stdlib.h>
# include <unistd.h>
# include "parser.h"

typedef struct s_exec	t_exec;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirections;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exec
{
	char	**envp;
	char	**local_vars;
	int		last_exit;
	t_cmd	*cmd_list;
	int		saved_in;
	int		saved_out;
}	t_exec;

typedef struct s_pipe_ctx
{
	int		**pipes;
	int		cmd_index;
	int		num_commands;
	pid_t	*pids;
}	t_pipe_ctx;

/* execute_simple_cmd.c */
int		run_external_cmd(t_cmd *cmd, t_exec *exec_ctx);
int		execute_simple_cmd(t_cmd *cmd, t_exec *exec_ctx);

/* simple_cmd_utils.c */
int		save_stdio(int *saved_in, int *saved_out);
void	restore_stdio(int saved_in, int saved_out);
int		get_exit_from_status(int status);
void	handle_execve_error(char *path, char *cmd_name, t_exec *exec_ctx);

/* redirection.c */
int		handle_input_redir(char *filename);
int		handle_output_redir(char *filename);
int		handle_append_redir(char *filename);
int		handle_heredoc(t_redir *redir);

/* redirection_utils.c */
int		apply_redirections(t_redir *redirections, t_exec *exec_ctx);

/* heredoc.c */
void	read_heredoc_lines(int write_fd, t_redir *redir, t_exec *exec_ctx);
int		process_heredocs(t_cmd *cmd, t_exec *exec_ctx);

/* heredoc_utils.c */
int		fork_heredoc_reader(t_redir *redir, t_exec *exec_ctx, int *pipe_fds);
int		process_heredoc_line(int write_fd, char *delim,
			int quoted, t_exec *exec_ctx);

/* path_resolution.c */
char	*resolve_cmd_path(char *command, t_exec *exec_ctx);

/* pipeline.c */
int		execute_pipeline(t_cmd *commands, t_exec *exec_ctx);

/* pipeline_utils.c */
int		count_commands(t_cmd *commands);
void	close_pipes(int **pipes, int num_pipes);
void	free_pipes(int **pipes, int count);
int		**create_pipes(int count);

/* pipeline_exec_utils.c */
int		process_all_heredocs(t_cmd *commands, t_exec *exec_ctx);
void	setup_pipe_redirections(int **pipes, int cmd_index, int num_commands);
void	execute_pipeline_command(t_cmd *cmd,
			t_exec *exec_ctx, t_pipe_ctx *pipe_ctx);

/* pipeline_child.c */
pid_t	fork_one_cmd(t_cmd *commands, t_cmd *current,
			t_exec *exec_ctx, t_pipe_ctx *pipe_ctx);
void	cleanup_pipes_and_exit(t_pipe_ctx *pipe_ctx,
			t_exec *exec_ctx, int code);
void	exec_cmd_child(t_cmd *cmd, t_exec *exec_ctx);

/* var_assignments.c */
int		count_leading_assignments(char **args);

/* dispatch_cmd.c */
int		dispatch_cmd(t_cmd *cmd, t_exec *exec_ctx);

#endif
