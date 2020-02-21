/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:30:16 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/21 15:03:35 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	rotation(t_player *pl)
{
	double	old_dir;
	double	old_plane;
	double	speed;

	old_dir = pl->dir_x;
	old_plane = pl->plane_x;
	speed = 0.02;
	if (pl->rightrot)
	{
		pl->dir_x = (pl->dir_x * cos(-speed) - pl->dir_y * sin(-speed));
		pl->dir_y = (old_dir * sin(-speed) + pl->dir_y * cos(-speed));
		pl->plane_x = (pl->plane_x * cos(-speed) - pl->plane_y * sin(-speed));
		pl->plane_y = (old_plane * sin(-speed) + pl->plane_y * cos(speed));
	}
	if (pl->leftrot)
	{
		pl->dir_x = (pl->dir_x * cos(speed) - pl->dir_y * sin(speed));
		pl->dir_y = (old_dir * sin(speed) + pl->dir_y * cos(speed));
		pl->plane_x = (pl->plane_x * cos(speed) - pl->plane_y * sin(speed));
		pl->plane_y = (old_plane * sin(speed) + pl->plane_y * cos(speed));
	}
}

int		can_move(int pos)
{
	if (pos == 1 || pos == 4)
		return (0);
	return (1);
}

void	mov_updown(t_player *pl, t_world *map, float speed)
{
	if (pl->forward)
	{
		if (can_move(map->worldmap[(int)(pl->pos_x + pl->dir_x * speed)]
			[(int)(pl->pos_y)]))
			pl->pos_x += pl->dir_x * speed * 0.5;
		if (can_move(map->worldmap[(int)(pl->pos_x)]
			[(int)(pl->pos_y + pl->dir_y * speed)]))
			pl->pos_y += pl->dir_y * speed * 0.5;
	}
	if (pl->backward)
	{
		if (can_move(map->worldmap[(int)(pl->pos_x - pl->dir_x * speed)]
			[(int)(pl->pos_y)]))
			pl->pos_x -= pl->dir_x * speed * 0.5;
		if (can_move(map->worldmap[(int)(pl->pos_x)]
			[(int)(pl->pos_y - pl->dir_y * speed)]))
			pl->pos_y -= pl->dir_y * speed * 0.5;
	}
}

void	mov_leftright(t_player *pl, t_world *map, float speed)
{
	if (pl->left)
	{
		if (can_move(map->worldmap[(int)(pl->pos_x)]
			[(int)(pl->pos_y + pl->dir_x * speed)]))
			pl->pos_y += pl->dir_x * speed * 0.5;
		if (can_move(map->worldmap[(int)(pl->pos_x - pl->dir_y * speed)]
			[(int)(pl->pos_y)]))
			pl->pos_x -= pl->dir_y * speed * 0.5;
	}
	if (pl->right)
	{
		if (can_move(map->worldmap[(int)(pl->pos_x)]
			[(int)(pl->pos_y - pl->dir_x * speed)]))
			pl->pos_y -= pl->dir_x * speed * 0.5;
		if (can_move(map->worldmap[(int)(pl->pos_x + pl->dir_y * speed)]
			[(int)(pl->pos_y)]))
			pl->pos_x += pl->dir_y * speed * 0.5;
	}
}

int		move(t_param *params)
{
	float speed;

	speed = 0.2;
	mov_updown(params->pl, params->map, speed);
	mov_leftright(params->pl, params->map, speed);
	rotation(params->pl);
	return (0);
}
