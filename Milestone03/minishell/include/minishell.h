/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:30:29 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/17 17:27:41 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <stdbool.h>

// Project headers
# include "libft.h"
# include "get_next_line.h"
# include "signals.h"
# include "lexer.h"
# include "parser.h"
# include "translation_function.h"
# include "executor.h"
# include "expander.h"
# include "builtins.h"
# include "main.h"

/* Exit codes */
# define EXIT_CMD_NOT_FOUND	127
# define EXIT_NOT_EXEC		126
# define EXIT_SIGINT		130

# define PROMPT "minishell$ "
# define HISTORY_FILE ".minishell_history"
# define MAX_HISTORY 1000
# define NO_QUOTE 0
# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2
# define LL_MAX "9223372036854775807"
# define LL_MIN "9223372036854775808"

#endif
