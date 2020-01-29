/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:17:45 by gsmets            #+#    #+#             */
/*   Updated: 2020/01/29 12:00:27 by gsmets           ###   ########.fr       */
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

void	fov_and_pos(int x, t_world *map, t_ray *ray, t_player *pl)
{
		pl->camera_x = 2 * x / (double)SCREENW - 1;
		ray->dir_x = pl->dir_x + pl->plane_x * pl->camera_x;
		ray->dir_y = pl->dir_y + pl->plane_y * pl->camera_x;
		map->x = (int)(pl->pos_x);
		map->y = (int)(pl->pos_y);
		ray->delta_x = fabs(1 / ray->dir_x);
		ray->delta_y = fabs(1 / ray->dir_y);

}

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

void	wallhit(t_world *map, t_ray *ray)
{
	int hit;

	hit = 0;
	while(hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			map->x += map->step_x;
			ray->wallside = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			map->y += map->step_y;
			ray->wallside = 1;
		}
		if (worldmap[map->x][map->y] > 0)
		{
			hit = 1;
		}
	}
}

void	walldist_dir(t_world *map, t_player *pl, t_ray *ray)
{
	if (ray->wallside == 1)
		{
			if (map->y < pl->pos_y)
				ray->walldir = 'W';
			else
				ray->walldir = 'E';
			ray->walldist = (map->y - pl->pos_y +
			(1 - map->step_y) / 2) / ray->dir_y;
			ray->wallx = pl->pos_x + ray->walldist * ray->dir_x;
		}
		else
		{
			if (map->x < pl->pos_x)
				ray->walldir = 'N';
			else
				ray->walldir = 'S';
			ray->walldist = (map->x - pl->pos_x +
			(1 - map->step_x) / 2) / ray->dir_x;
			ray->wallx = pl->pos_y + ray->walldist * ray->dir_y;
		}
}

void	raycast(t_player *pl, t_mlx *mlx, t_world *map, t_ray *ray)
{
	int x;
	int side;

	x = 0;
	while(x < SCREENW)
	{
		fov_and_pos(x, map, ray, pl);
		get_step(map, ray, pl);
		wallhit(map, ray);
		walldist_dir(map, pl, ray);
		mlx->l_height = (int)(SCREENH / ray->walldist);
		mlx->l_start = (mlx->l_height * -1) / 2 + SCREENH / 2;
		if (mlx->l_start < 0)
			mlx->l_start = 0;
		mlx->l_end = mlx->l_height / 2 + SCREENH / 2;
		if (mlx->l_end >= SCREENH)
			mlx->l_end = SCREENH - 1;

		if (ray->walldir == 'N')
		{
			mlx->txt_data = mlx->txt->txt1_data;
			mlx->text_sl = mlx->txt->text1_sl;
			mlx->text_h = mlx->txt->text1_h;
		}
		else if (ray->walldir == 'S')
		{
			mlx->txt_data = mlx->txt->txt2_data;
			mlx->text_sl = mlx->txt->text2_sl;
			mlx->text_h = mlx->txt->text2_h;
		}
				else if (ray->walldir == 'E')
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

		ray->wallx -= floor(ray->wallx);
		mlx->text_x = ray->wallx * (mlx->text_sl / 4);
		drawline(mlx, x, mlx->text_x);
		x++;
	}
}
