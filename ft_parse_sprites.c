/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_sprites.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:39:20 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/21 15:06:08 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int			count_sprites(t_world *map)
{
	int x;
	int y;
	int count;

	x = 0;
	while (x < map->max_x)
	{
		y = 0;
		while (y < map->max_y)
		{
			if (map->worldmap[x][y] == 4)
				count++;
			y++;
		}
		x++;
	}
	return (count);
}

t_spriteptr	*get_sprites(t_param *p)
{
	t_spriteptr	*sprites;
	int			x;
	int			y;
	int			i;

	p->mlx->spr_number = count_sprites(p->map);
	sprites = (malloc(p->mlx->spr_number * sizeof(t_spriteptr)));
	p->mlx->spr_order = (malloc(p->mlx->spr_number * sizeof(int)));
	x = 0;
	i = 0;
	while (x < p->map->max_x)
	{
		y = 0;
		while (y < p->map->max_y)
		{
			if (p->map->worldmap[x][y] == 4)
			{
				sprites[i].x = x;
				sprites[i++].y = y;
			}
			y++;
		}
		x++;
	}
	return (sprites);
}
