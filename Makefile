SRCS	= $(wildcard ft*.c)

OBJS	= $(SRCS:.c=.o)

NAME	= cub3d.out

GCC		= gcc

FLAGS	= -Wall -Wextra -Werror

INCLUDEH	= -I minilibx

MLX_DIR		=	minilibx_opengl



all:	$(NAME)

.PHONY:	clean fclean re bonus bench bclean

$(NAME):	$(OBJS)
	$(MAKE) -C libft
	$(MAKE) -C minilibx_opengl
	gcc $(FLAGS) -o $(NAME) $(OBJS) -L libft -lft -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f screenshot.bmp

re: fclean all

%.o: %.c
	$(GCC) $(INCLUDEH) -c $<  -o $(<:.c=.o)

run: all
	@./cub3d.out