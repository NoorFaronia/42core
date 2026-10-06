# Program name
NAME = minishell

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror

# get_next_line
GNL_DIR = src/get_next_line

GNL_SRC = $(GNL_DIR)/get_next_line.c \
          $(GNL_DIR)/get_next_line_utils.c

# Sources
SRC =	src/main/main.c\
	src/main/prompt.c\
	src/main/history.c\
	src/main/history_utils.c\
	src/main/error_clean_utils.c\
	src/main/main_utils.c\
	src/signals/signals.c\
	src/lexer/lexer.c\
	src/lexer/word_lexer.c\
	src/lexer/utils_lexer.c\
	src/parser/parser.c\
	src/parser/parse_pipe.c\
	src/parser/parse_cmd.c\
	src/parser/add_arg.c\
	src/parser/add_redir.c\
	src/translation_function/translation_function.c\
	src/executor/execute_simple_cmd.c\
	src/executor/heredoc_utils.c\
	src/executor/pipeline.c\
	src/executor/redirection.c\
	src/executor/var_assignments.c\
	src/executor/path_resolution.c\
	src/executor/pipeline_exec_utils.c\
	src/executor/redirection_utils.c\
	src/executor/heredoc.c\
	src/executor/pipeline_child.c\
	src/executor/pipeline_utils.c\
	src/executor/simple_cmd_utils.c\
	src/executor/dispatch_cmd.c\
	src/expander/expander.c\
	src/expander/expander_args.c\
	src/expander/expander_quotes.c\
	src/expander/expander_redirs.c\
	src/expander/expander_variables.c\
	src/builtins/cd.c\
	src/builtins/builtins.c\
	src/builtins/echo.c\
	src/builtins/env.c\
	src/builtins/exit.c\
	src/builtins/export.c\
	src/builtins/env_modify.c\
	src/builtins/env_utils.c\
	src/builtins/pwd.c\
	src/builtins/unset.c\
	$(GNL_SRC)

# Objects
OBJS = $(SRC:.c=.o)

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

READLINE = -lreadline

# Includes
INC = -Ilibft -Iinclude -Isrc/get_next_line

# Default rule
all: $(LIBFT) $(NAME)

# Build program
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

# Compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Libft compilation
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Clean object files
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

# Full clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f .minishell_history

# Recompile
re: fclean all

.PHONY: all clean fclean re
