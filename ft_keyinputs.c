/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyinputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:30:16 by gsmets            #+#    #+#             */
/*   Updated: 2020/01/28 14:53:26 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	rotation(int key, t_player *pl)
{
	double	old_dir;
	double	old_plane;
	double	speed;

	old_dir = pl->dir_x;
	old_plane = pl->plane_x;
	speed = 0.08;
	if (key == 124) // RIGHT ROT
	{
		pl->dir_x = (pl->dir_x * cos(-speed) - pl->dir_y * sin(-speed));
		pl->dir_y = (old_dir * sin(-speed) + pl->dir_y * cos(-speed));
		pl->plane_x = (pl->plane_x * cos(-speed) - pl->plane_y * sin(-speed));
		pl->plane_y = (old_plane * sin(-speed) + pl->plane_y * cos(speed));
	}
	if (key == 123) // LEFT ROT
	{
		pl->dir_x = (pl->dir_x * cos(speed) - pl->dir_y * sin(speed));
		pl->dir_y = (old_dir * sin(speed) + pl->dir_y * cos(speed));
		pl->plane_x = (pl->plane_x * cos(speed) - pl->plane_y * sin(speed));
		pl->plane_y = (old_plane * sin(speed) + pl->plane_y * cos(speed));
	}
}

void	mov_updown(int key, t_player *pl, t_world *map, float speed)
{
	if (key == 13) // UP
	{
		pl->pos_x += pl->dir_x * speed;
		pl->pos_y += pl->dir_y * speed;
	}
	if (key == 1) // DOWN
	{
		pl->pos_x -= pl->dir_x * speed;
		pl->pos_y -= pl->dir_y * speed;
	}
}

void	mov_leftright(int key, t_player *pl, t_world *map, float speed)
{
	if (key == 0) // LEFT
	{
		pl->pos_y += pl->dir_x * speed;
		pl->pos_x -= pl->dir_y * speed;
	}
	if (key == 2) // RIGHT
	{
		pl->pos_y -= pl->dir_x * speed;
		pl->pos_x += pl->dir_y * speed;
	}
}

int		key_input(int key, t_param *params)
{
	float speed;

	speed = 0.3;
	if (key == 1 || key == 13)
		mov_updown(key, params->pl, params->map, speed);
	else if (key == 0 || key == 2)
		mov_leftright(key, params->pl, params->map, speed);
	else if (key == 123 || key == 124)
		rotation(key, params->pl);
	return (0);
}
