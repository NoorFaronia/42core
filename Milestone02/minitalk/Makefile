# Programs
SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Sources
SRC_SERVER = server.c
SRC_CLIENT = client.c
SRC_SERVER_BONUS = server_bonus.c
SRC_CLIENT_BONUS = client_bonus.c

# Objects
OBJS_SERVER = $(SRC_SERVER:.c=.o)
OBJS_CLIENT = $(SRC_CLIENT:.c=.o)
OBJS_SERVER_BONUS = $(SRC_SERVER_BONUS:.c=.o)
OBJS_CLIENT_BONUS = $(SRC_CLIENT_BONUS:.c=.o)

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)

# Default rule
all: $(LIBFT) $(SERVER) $(CLIENT)

# Bonus
bonus: $(LIBFT) $(SERVER_BONUS) $(CLIENT_BONUS)

# Libft compilation
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# General rule to compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) $(LIBFT_INC) -c $< -o $@

# Server compilation
$(SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFT) -o $(SERVER)

# Client compilation
$(CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFT) -o $(CLIENT)

# Server_bonus compilation
$(SERVER_BONUS): $(OBJS_SERVER_BONUS)
	$(CC) $(CFLAGS) $(OBJS_SERVER_BONUS) $(LIBFT) -o $(SERVER_BONUS)

# Client_bonus compilation
$(CLIENT_BONUS): $(OBJS_CLIENT_BONUS)
	$(CC) $(CFLAGS) $(OBJS_CLIENT_BONUS) $(LIBFT) -o $(CLIENT_BONUS)

# Clean object files
clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean

# Full clean
fclean: clean
	rm -f $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Recompile
re: fclean all

.PHONY: all bonus clean fclean re
