SRCS	=	ft_checkmap.c\
			ft_cub3d.c\
			ft_cubatoi.c\
			ft_drawing.c\
			ft_errors.c\
			ft_init.c\
			ft_keypress.c\
			ft_movement.c\
			ft_parse_map.c\
			ft_parse_param.c\
			ft_parse_player.c\
			ft_parse_sprites.c\
			ft_parse_textures.c\
			ft_parse.c\
			ft_raycast.c\
			ft_screenshot.c\
			ft_sprites.c

OBJS	= $(SRCS:.c=.o)

NAME	= cub3D

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