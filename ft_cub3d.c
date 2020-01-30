/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:43:55 by gsmets            #+#    #+#             */
/*   Updated: 2020/01/30 14:11:58 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"
#include <stdlib.h>

int		run_game(t_param *p)
{
	move(p);
	raycast(p->pl, p->mlx, p->map, p->ray);
	mlx_put_image_to_window(p->mlx->ptr, p->mlx->win, p->mlx->img, 0, 0);
	return (0);
}

int close_game(void *coucou)
{
	exit(EXIT_SUCCESS);
}

int		main()
{
	t_mlx		mlx;
	t_player	one;
	t_world		map;
	t_ray		ray;
	t_param		params;
	t_txt		text;

	params.mlx = &mlx;
	params.pl = &one;
	params.map = &map;
	params.ray = &ray;
	mlx.txt = &text;
	player_init(&one);
	mlx.screen_h = 1000;
	mlx.screen_w = 1000;
	if (!(mlx.ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(mlx.win = mlx_new_window(mlx.ptr, mlx.screen_w, mlx.screen_h, "cub3d")))
		return (EXIT_FAILURE);
	mlx.img = mlx_new_image(mlx.ptr, mlx.screen_w, mlx.screen_h);
	txt_init(&text, &mlx);
	mlx.d_ad = (int *)mlx_get_data_addr(mlx.img, &(mlx.bits), &(mlx.sl), &(mlx.ed));
	mlx_hook(mlx.win, 2, 1, key_press, (void *)&params);
	mlx_key_hook(mlx.win, key_release, (void *)&params);
	mlx_hook(mlx.win, 17, 1, close_game, (void *)&params);
	mlx_loop_hook ( mlx.ptr, run_game, (void *)&params);
	mlx_loop(mlx.ptr);
}
