/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:43:55 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/10 13:09:28 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int worldmap[MAPW][MAPH] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	make_map(int map[24][24], int wmap[24][24], int x, int y)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < x)
	{
		while(j < y)
		{
			map[i][j] = wmap[i][j];
			j++;
		}
		j = 0;
		i++;
	}
}

int		run_game(t_param *p)
{
	move(p);
	raycast(p->pl, p->mlx, p->map, p->ray);
	drawsprites(p->mlx, p->pl, p->map, p->ray);
	mlx_put_image_to_window(p->mlx->ptr, p->mlx->win, p->mlx->img, 0, 0);
	return (0);
}

int close_game(void *coucou)
{
	void *hey;

	hey = coucou;
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
	t_sprite	sprite;

	params.mlx = &mlx;
	params.pl = &one;
	params.map = &map;
	params.ray = &ray;
	mlx.txt = &text;
	mlx.sprite = &sprite;
	player_init(&one);
	make_map(map.worldmap, worldmap, MAPW, MAPH);
	mlx.screen_h = 720;
	mlx.screen_w = 1280;
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
