NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCE = ft_printf.c \
       printf_c.c \
       printf_s.c \
       printf_di.c \
       printf_u.c \
       printf_x.c \
       printf_p.c

OBJS = $(SRCE:.c=.o)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
