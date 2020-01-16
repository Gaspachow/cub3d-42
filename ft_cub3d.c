/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:43:55 by gsmets            #+#    #+#             */
/*   Updated: 2020/01/16 15:53:54 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mlx.h>
#define MAPW 24
#define MAPH 24
#define SCREENW 64
#define SCREENH 64
#define H 64

typedef struct		mlx_s
{
	void			*ptr;
	void			*win;
	int				l_height;
	int				l_start;
	int				l_end;
	int				color;
}					mlx_t;

typedef struct		player_s
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
}					player_t;

typedef struct		world_s
{
	double			time;
	double			oldtime;
	int				x;
	int				y;
	int				step_x;
	int				step_y;
}					world_t;

typedef struct		ray_s
{
	double			dir_x;
	double			dir_y;
	double			side_x;
	double			side_y;
	double			delta_x;
	double			delta_y;
	double			walldist;
}					ray_t;

typedef struct		param_s
{
	mlx_t			*mlx;
	player_t		*pl;
	world_t			*map;
	ray_t			*ray;
}					param_t;

int worldmap[MAPW][MAPH] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
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

int drawline(mlx_t *mlx, int x)
{
	int i;

	i = mlx->l_start;
	while (i <= mlx->l_end)
	{
		mlx_pixel_put(mlx->ptr, mlx->win, x, i, mlx->color);
		i++;
	}
	return (1);
}


int	rgb_int(int red, int green, int blue)
{
	int	rgb;
	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

void	player_init(player_t *pl)
{
	pl->pos_x = 22;
	pl->pos_y = 12;
	pl->dir_x = -1;
	pl->dir_y = 0;
	pl->plane_x = 0;
	pl->plane_y = 0.66;
}

void	get_step(world_t *map, ray_t *ray, player_t *pl)
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

void	raycast(player_t *pl, mlx_t *mlx, world_t *map, ray_t *ray)
{
	int x;
	int hit;
	int side;

	x = 0;
	mlx_clear_window (mlx->ptr, mlx->win);
	while(x < SCREENW)
	{
		pl->camera_x = 2 * x / (double)SCREENW - 1;
		ray->dir_x = pl->dir_x + pl->plane_x * pl->camera_x;
		ray->dir_y = pl->dir_y + pl->plane_y * pl->camera_x;

		map->x = (int)(pl->pos_x);
		map->y = (int)(pl->pos_y);
		ray->delta_x = fabs(1 / ray->dir_x);
		ray->delta_y = fabs(1 / ray->dir_y);

		get_step(map, ray, pl);
		while(!hit)
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
				hit = 1;
		}

		if (!side)
			ray->walldist = (map->x - pl->pos_x + (1 - map->step_x) / 2) / ray->dir_x;
		else
			ray->walldist = (map->y - pl->pos_y + (1 - map->step_y) / 2) / ray->dir_y;

		mlx->l_height = (int)(SCREENH / ray->walldist);
		mlx->l_start = (mlx->l_height * -1) / 2 + SCREENH / 2;
		if (mlx->l_start < 0)
			mlx->l_start = 0;
		mlx->l_end = mlx->l_height / 2 + SCREENH / 2;
		if (mlx->l_end >= SCREENH)
			mlx->l_end = SCREENH - 1;

		switch(worldmap[map->x][map->y])
    	{
        case 1:  mlx->color = rgb_int(204, 0, 0);  break; //red
        case 2:  mlx->color = rgb_int(128, 255, 0);  break; //green
        case 3:  mlx->color = rgb_int(0, 128, 255);   break; //blue
        case 4:  mlx->color = rgb_int(255, 255, 255);  break; //white
        default: mlx->color = rgb_int(255, 255, 0); break; //yellow
    	}

		if (side == 1)
			mlx->color /= 2;
		printf("walldist is %f - line height is %i - Start is %i - end is %i\n", ray->walldist, mlx->l_height, mlx->l_start, mlx->l_end);
		drawline(mlx, x);
		x++;
	}
}

int	run_game(int key, param_t *params)
{
	mlx_t		*mlx;
	player_t	*pl;
	world_t		*map;
	ray_t		*ray;

	mlx = params->mlx;
	pl = params->pl;
	map = params->map;
	ray = params->ray;
	raycast(pl, mlx, map, ray);
	return (0);
}

int main()
{
	mlx_t		mlx;
	player_t	one;
	world_t		map;
	ray_t		ray;
	param_t		params;

	params.mlx = &mlx;
	params.pl = &one;
	params.map = &map;
	params.ray = &ray;

	player_init(&one);
	if (!(mlx.ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(mlx.win = mlx_new_window(mlx.ptr, SCREENW, SCREENH, "cub3d")))
		return (EXIT_FAILURE);
	mlx_hook(mlx.win, 2, 1, run_game, (void *)&params);
	mlx_loop(mlx.ptr);
}


