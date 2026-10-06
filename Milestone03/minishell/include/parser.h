/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:46:08 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/17 17:24:26 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include "lexer.h"

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE
}	t_node_type;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int				heredoc_pipe;
	int				quoted;
	int				ambiguous;
	struct s_redir	*next;
}	t_redir;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**args;
	int				*args_quoted;
	t_redir			*redirs;
}	t_ast;

typedef struct s_parser
{
	t_token	*current;
	int		error;
}	t_parser;

// parser.c
void	parse_error(char *msg);
void	free_ast(t_ast *node);
t_ast	*parser(t_token *tokens);

// add_arg.c
void	add_arg(t_ast *node, t_parser *pars);

// add_redir.c
void	add_redir(t_ast *node, t_parser *pars);
void	free_redir(t_redir *redir);

// parse_cmd.c
void	next_token(t_parser *pars);
t_ast	*parse_cmd(t_parser *pars);

// parse_pipe.c
t_ast	*parse_pipe(t_parser *pars);

#endif
