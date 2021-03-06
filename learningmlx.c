/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learningmlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:49:14 by gas               #+#    #+#             */
/*   Updated: 2020/02/21 15:48:03 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mlx.h>

typedef struct		s_data
{
	void			*mlx_ptr;
	void			*mlx_win;
}					t_data;

typedef struct		s_img
{
	int				x;
	int				y;
	int				h;
	int				w;
	void			*ptr;
	void			*win;
	void			*mlx;
}					t_img;

int	rgb_int(int red, int green, int blue)
{
	int	rgb;
	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

int	test(int i)
{
	printf("Key value is %i\n", i);
	i++;
	return (1);
}

int	deal_key(int key, t_img *datapepe)
{
	test(key);
	if (key == 13)
		{
			datapepe->y -= 10;
			mlx_clear_window (datapepe->mlx, datapepe->win);
			mlx_put_image_to_window(datapepe->mlx, datapepe->win, datapepe->ptr, datapepe->x, datapepe->y);
		}
		if (key == 1)
		{
			datapepe->y += 10;
			mlx_clear_window (datapepe->mlx, datapepe->win);
			mlx_put_image_to_window(datapepe->mlx, datapepe->win, datapepe->ptr, datapepe->x, datapepe->y);
		}
				if (key == 0)
		{
			datapepe->x -= 10;
			mlx_clear_window (datapepe->mlx, datapepe->win);
			mlx_put_image_to_window(datapepe->mlx, datapepe->win, datapepe->ptr, datapepe->x, datapepe->y);
		}
				if (key == 2)
		{
			datapepe->x += 10;
			mlx_clear_window (datapepe->mlx, datapepe->win);
			mlx_put_image_to_window(datapepe->mlx, datapepe->win, datapepe->ptr, datapepe->x, datapepe->y);
		}
	return (0);
}

int	main(void)
{
	t_data	data;
	int		i;
	t_img	datapepe;

	datapepe.x = 900;
	datapepe.y = 500;
	datapepe.h = 50;
	datapepe.w = 50;

	i = 0;
	if (!(data.mlx_ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(data.mlx_win = mlx_new_window(data.mlx_ptr, 1600, 720, "coucou")))
		return (EXIT_FAILURE);
	datapepe.mlx = data.mlx_ptr;
	datapepe.win = data.mlx_win;
	datapepe.ptr = mlx_xpm_file_to_image(data.mlx_ptr, "textures/cat1.xpm", &datapepe.h, &datapepe.w);
	printf("height and width are %i and %i", datapepe.h, datapepe.w);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, datapepe.ptr, 900, 500);

	mlx_hook(data.mlx_win, 2, 1, deal_key, (void *)&datapepe);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}
