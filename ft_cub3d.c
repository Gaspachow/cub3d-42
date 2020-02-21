/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:43:55 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/21 14:53:30 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		run_game(t_param *p)
{
	move(p);
	raycast(p->pl, p->mlx, p->map, p->ray);
	drawsprites(p->mlx, p->pl, p->map, p->ray);
	if (!p->screenshot)
		mlx_put_image_to_window(p->mlx->ptr, p->mlx->win, p->mlx->img, 0, 0);
	return (0);
}

int		close_game(t_param *p)
{
	int i;

	i = 0;
	if (p->lines)
	{
		while (p->lines[i])
		{
			free(p->lines[i]);
			i++;
		}
		free(p->lines);
	}
	exit(EXIT_SUCCESS);
}

int		start_all(t_param *p, int ac, char **av)
{
	t_txt	text;

	p->mlx->txt = &text;
	parse_cub(av[1], p);
	if (!(p->mlx->ptr = mlx_init()))
		put_error("ERROR\n Mlx function failed", p);
	txt_init(p->mlx->txt, p->mlx);
	p->mlx->img = mlx_new_image(p->mlx->ptr, p->mlx->screen_w,
				p->mlx->screen_h);
	p->mlx->d_ad = (int *)mlx_get_data_addr(p->mlx->img,
				&(p->mlx->bits), &(p->mlx->sl), &(p->mlx->ed));
	if (ac == 3)
		make_screenshot(p, av[2]);
	if (!(p->mlx->win = mlx_new_window(p->mlx->ptr, p->mlx->screen_w,
		p->mlx->screen_h, "cub3d")))
		put_error("ERROR\n Mlx function failed", p);
	mlx_hook(p->mlx->win, 2, 1, key_press, (void *)p);
	mlx_key_hook(p->mlx->win, key_release, (void *)p);
	mlx_hook(p->mlx->win, 17, 1, close_game, (void *)p);
	mlx_loop_hook(p->mlx->ptr, run_game, (void *)p);
	mlx_loop(p->mlx->ptr);
	return (1);
}

int		main(int ac, char **av)
{
	t_mlx		mlx;
	t_player	one;
	t_world		map;
	t_ray		ray;
	t_param		params;

	params.mlx = &mlx;
	params.pl = &one;
	params.map = &map;
	params.ray = &ray;
	params.lines = 0;
	if (ac > 3)
		put_error("ERROR\nTOO MANY ARGUMENTS\n", &params);
	if (ac < 2)
		put_error("ERROR\nNOT ENOUGH ARGUMENTS\n", &params);
	start_all(&params, ac, av);
}
