
SRCS	= $(wildcard ft*.c)

OBJS	= $(SRCS:.c=.o)

NAME	= cub3d.out

GCC		= gcc

FLAGS	= -Wall -Wextra -Werror

INCLUDEH	= -I /usr/X11/include -g -l mlx -framework OpenGL -framework AppKit



all:	$(NAME)

.PHONY:	clean fclean re bonus bench bclean

$(NAME):	$(OBJS)
	gcc $(INCLUDEH) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	$(GCC) -c $<  -o $(<:.c=.o)

run: all
	@./cub3d.out
