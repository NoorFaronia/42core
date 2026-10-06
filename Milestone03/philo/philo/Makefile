# Program name
NAME = philo

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror
PTHREAD = -pthread

# Sources
SRC =	src/main.c\
	src/initializing.c\
	src/philo_life_utils.c\
	src/philo_life.c\
	src/utils.c\
	src/philo_died.c

# Objects
OBJ = $(SRC:.c=.o)

# Includes
INC = -Iinclude

# Default rule
all: $(NAME)

# Build program
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(PTHREAD) $(OBJ) -o $(NAME)

# Compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) $(INC) $(PTHREAD) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJ)

# Full clean
fclean: clean
	rm -f $(NAME)

# Recompile
re: fclean all

.PHONY: all clean fclean re