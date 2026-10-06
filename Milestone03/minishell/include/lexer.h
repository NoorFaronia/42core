/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:44:00 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/17 15:19:20 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				quoted;
	struct s_token	*next;
}	t_token;

// lexer.c
t_token	*lexer(char *line);

// utils_lexer.c
int		add_token(t_token	**tokens, t_token_type type,
			char *value, int quoted);
void	free_tokens(t_token *tokens);
int		quote(char **tokens_word, char *line, int *i);

// word_lexer.c
int		word(char *line, int *i, t_token **tokens);
#endif
