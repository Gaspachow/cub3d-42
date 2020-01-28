/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:17:45 by gsmets            #+#    #+#             */
/*   Updated: 2020/01/28 15:27:41 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int worldmap[MAPW][MAPH] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	get_step(t_world *map, t_ray *ray, t_player *pl)
{
	if (ray->dir_x < 0)
	{
		map->step_x = -1;
		ray->side_x = (pl->pos_x - map->x) * ray->delta_x;
	}
	else
	{
		map->step_x = 1;
		ray->side_x = (map->x + 1.0 - pl->pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		map->step_y = -1;
		ray->side_y = (pl->pos_y - map->y) * ray->delta_y;
	}
	else
	{
		map->step_y = 1;
		ray->side_y = (map->y + 1.0 - pl->pos_y) * ray->delta_y;
	}
}

void	raycast(t_player *pl, t_mlx *mlx, t_world *map, t_ray *ray)
{
	int x;
	int hit;
	int side;
	int walldir;
	double wallx;

	x = 0;
	while(x < SCREENW)
	{
		hit = 0;
		pl->camera_x = 2 * x / (double)SCREENW - 1;
		ray->dir_x = pl->dir_x + pl->plane_x * pl->camera_x;
		ray->dir_y = pl->dir_y + pl->plane_y * pl->camera_x;

		map->x = (int)(pl->pos_x);
		map->y = (int)(pl->pos_y);
		ray->delta_x = fabs(1 / ray->dir_x);
		ray->delta_y = fabs(1 / ray->dir_y);

		get_step(map, ray, pl);

		walldir = 0;
		while(hit == 0)
		{
			if (ray->side_x < ray->side_y)
			{
				ray->side_x += ray->delta_x;
				map->x += map->step_x;
				side = 0;
			}
			else
			{
				ray->side_y += ray->delta_y;
				map->y += map->step_y;
				side = 1;
			}
			if (worldmap[map->x][map->y] > 0)
			{
				hit = 1;
			}
		}

		if (side == 1)
		{
			if (map->y < pl->pos_y)
				walldir = 'W';
			else
				walldir = 'E';
			ray->walldist = (map->y - pl->pos_y +
			(1 - map->step_y) / 2) / ray->dir_y;
			wallx = pl->pos_x + ray->walldist * ray->dir_x;
		}
		else
		{
			if (map->x < pl->pos_x)
				walldir = 'N';
			else
				walldir = 'S';
			ray->walldist = (map->x - pl->pos_x +
			(1 - map->step_x) / 2) / ray->dir_x;
			wallx = pl->pos_y + ray->walldist * ray->dir_y;
		}

		mlx->l_height = (int)(SCREENH / ray->walldist);
		mlx->l_start = (mlx->l_height * -1) / 2 + SCREENH / 2;
		if (mlx->l_start < 0)
			mlx->l_start = 0;
		mlx->l_end = mlx->l_height / 2 + SCREENH / 2;
		if (mlx->l_end >= SCREENH)
			mlx->l_end = SCREENH - 1;

		if (walldir == 'N')
		{
			mlx->txt_data = mlx->txt->txt1_data;
			mlx->text_sl = mlx->txt->text1_sl;
			mlx->text_h = mlx->txt->text1_h;
		}
		else if (walldir == 'W')
		{
			mlx->txt_data = mlx->txt->txt2_data;
			mlx->text_sl = mlx->txt->text2_sl;
			mlx->text_h = mlx->txt->text2_h;
		}
				else if (walldir == 'E')
		{
			mlx->txt_data = mlx->txt->txt3_data;
			mlx->text_sl = mlx->txt->text3_sl;
			mlx->text_h = mlx->txt->text3_h;
		}
		else
		{
			mlx->txt_data = mlx->txt->txt4_data;
			mlx->text_sl = mlx->txt->text4_sl;
			mlx->text_h = mlx->txt->text4_h;
		}

		wallx -= floor(wallx);
		mlx->text_x = wallx * (mlx->text_sl / 4);
		drawline(mlx, x, mlx->text_x);
		x++;
	}
}
