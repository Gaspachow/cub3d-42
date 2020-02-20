/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:43:55 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/20 17:26:05 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		run_game(t_param *p)
{
	move(p);
	raycast(p->pl, p->mlx, p->map, p->ray);
	drawsprites(p->mlx, p->pl, p->map, p->ray);
	mlx_put_image_to_window(p->mlx->ptr, p->mlx->win, p->mlx->img, 0, 0);
	return (0);
}

int		close_game(t_param *coucou)
{
	void *hey;
	
	hey = coucou;
	make_screenshot(coucou->mlx);
	exit(EXIT_SUCCESS);
}

int		main(int ac, char **av)
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
	if (ac > 3)
		put_error("ERROR\nTOO MANY ARGUMENTS\n", &params);
	if (ac < 2)
		put_error("ERROR\nNOT ENOUGH ARGUMENTS\n", &params);
	parse_cub(av[1], &params);
	if (ac == 3)
		if (ft_strncmp("--saved", av[2], 8))
			make_screenshot(&mlx);
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
