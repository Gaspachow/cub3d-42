/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:43:55 by gsmets            #+#    #+#             */
/*   Updated: 2020/01/27 14:13:17 by gsmets           ###   ########.fr       */
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
#define SCREENW 640
#define SCREENH 480

typedef	struct		textures_s
{
	void			*texture1;
	int				*texture1_data;
	int				text1_h;
	int				text1_w;
	int				text1_sizeline;
	int				text1_sizebit;
	int				text1_endian;
	void			*texture2;
	int				*texture2_data;
	int				text2_h;
	int				text2_w;
	int				text2_sizeline;
	int				text2_sizebit;
	int				text2_endian;
	void			*texture3;
	int				*texture3_data;
	int				text3_h;
	int				text3_w;
	int				text3_sizeline;
	int				text3_sizebit;
	int				text3_endian;
	void			*texture4;
	int				*texture4_data;
	int				text4_h;
	int				text4_w;
	int				text4_sizeline;
	int				text4_sizebit;
	int				text4_endian;
}					texture_t;

typedef struct		mlx_s
{
	void			*ptr;
	void			*win;
	void			*img;
	int				*data_addr;
	int				bits;
	int				size_line;
	int				endian;
	int				l_height;
	int				l_start;
	int				l_end;
	int				color;
	texture_t		*texture;
	int				*texture_data;
	int				text_sizeline;
	int				text_h;
	int				text_x;

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

int	rgb_int(int red, int green, int blue)
{
	int	rgb;
	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

int drawline(mlx_t *mlx, int x, int text_x)
{
	int i;
	int j;
	int *text;
	double step;

	i = 0;
	j = 0;
	step = 1.0 * mlx->text_h / mlx->l_height;
	double pos = (mlx->l_start - SCREENH / 2 + mlx->l_height / 2) * step;
	text = mlx->texture_data;
	while (i < mlx->l_start)
	{
		*(mlx->data_addr + x + i * mlx->size_line / 4) = rgb_int(135, 197, 214);
		i++;
	}

	while (i < mlx->l_end)
	{
		*(mlx->data_addr + x + i * mlx->size_line / 4) = *(text + text_x + (int)pos * mlx->text_sizeline / 4);
		i++;
		pos += step;
	}

	while (i < SCREENH)
	{
		*(mlx->data_addr + x + i * mlx->size_line / 4) = rgb_int(125, 125, 125);
		i++;
	}
	return (1);
}

void	player_init(player_t *pl)
{
	pl->pos_x = 22;
	pl->pos_y = 10;
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
			ray->walldist = (map->y - pl->pos_y + (1 - map->step_y) / 2) / ray->dir_y;
			wallx = pl->pos_x + ray->walldist * ray->dir_x;
		}
		else
		{
			if (map->x < pl->pos_x)
				walldir = 'N';
			else
				walldir = 'S';
			ray->walldist = (map->x - pl->pos_x + (1 - map->step_x) / 2) / ray->dir_x;
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
			mlx->texture_data = mlx->texture->texture1_data;
			mlx->text_sizeline = mlx->texture->text1_sizeline;
			mlx->text_h = mlx->texture->text1_h;
		}
		else if (walldir == 'W')
		{
			mlx->texture_data = mlx->texture->texture2_data;
			mlx->text_sizeline = mlx->texture->text2_sizeline;
			mlx->text_h = mlx->texture->text2_h;
		}
				else if (walldir == 'E')
		{
			mlx->texture_data = mlx->texture->texture3_data;
			mlx->text_sizeline = mlx->texture->text3_sizeline;
			mlx->text_h = mlx->texture->text3_h;
		}
		else
		{
			mlx->texture_data = mlx->texture->texture4_data;
			mlx->text_sizeline = mlx->texture->text4_sizeline;
			mlx->text_h = mlx->texture->text4_h;
		}

		wallx -= floor(wallx);
		mlx->text_x = wallx * (mlx->text_sizeline / 4);
		// mlx->text_x = (mlx->text_sizeline / 4) - mlx->text_x - 1;
		// if (side == 0 && ray->dir_x > 0)
		// 	mlx->text_x = (mlx->text_sizeline / 4) - mlx->text_x -1;
		// else if (side == 1 && ray->dir_y < 0)
		// 	mlx->text_x = (mlx->text_sizeline / 4) - mlx->text_x -1;
		// wallx -= floor(wallx);
		// mlx->text_x = wallx * mlx->text_sizeline / 4;

		drawline(mlx, x, mlx->text_x);
		x++;
	}
}

void	rotation(int key, player_t *pl)
{
	double	old_dir;
	double	old_plane;
	double	speed;

	old_dir = pl->dir_x;
	old_plane = pl->plane_x;
	speed = 0.08;
	if (key == 124)
	{
		pl->dir_x = (pl->dir_x * cos(-speed) - pl->dir_y * sin(-speed));
		pl->dir_y = (old_dir * sin(-speed) + pl->dir_y * cos(-speed));
		pl->plane_x = (pl->plane_x * cos(-speed) - pl->plane_y * sin(-speed));
		pl->plane_y = (old_plane * sin(-speed) + pl->plane_y * cos(speed));
	}
	if (key == 123)
	{
		pl->dir_x = (pl->dir_x * cos(speed) - pl->dir_y * sin(speed));
		pl->dir_y = (old_dir * sin(speed) + pl->dir_y * cos(speed));
		pl->plane_x = (pl->plane_x * cos(speed) - pl->plane_y * sin(speed));
		pl->plane_y = (old_plane * sin(speed) + pl->plane_y * cos(speed));
	}
}

int		movement(int key, param_t *params)
{
	double speed;

	speed = 0.3;
	if (key == 13)
	{
		params->pl->pos_x += params->pl->dir_x * speed;
		params->pl->pos_y += params->pl->dir_y * speed;
	}
	if (key == 1)
	{
		params->pl->pos_x -= params->pl->dir_x * speed;
		params->pl->pos_y -= params->pl->dir_y * speed;
	}
	if (key == 0)
	{
		params->pl->pos_y += params->pl->dir_x * speed;
		params->pl->pos_x -= params->pl->dir_y * speed;
	}
	if (key == 2)
	{
		params->pl->pos_y -= params->pl->dir_x * speed;
		params->pl->pos_x += params->pl->dir_y * speed;
	}
	if (key == 123 || key == 124)
		rotation(key, params->pl);
	return (0);
}

int	run_game(param_t *params)
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
	mlx_put_image_to_window(params->mlx->ptr, params->mlx->win, params->mlx->img, 0, 0);
	return (0);
}

int main()
{
	mlx_t		mlx;
	player_t	one;
	world_t		map;
	ray_t		ray;
	param_t		params;
	texture_t	text;

	params.mlx = &mlx;
	params.pl = &one;
	params.map = &map;
	params.ray = &ray;
	mlx.texture = &text;

	player_init(&one);
	if (!(mlx.ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(mlx.win = mlx_new_window(mlx.ptr, SCREENW, SCREENH, "cub3d")))
		return (EXIT_FAILURE);
	mlx.img = mlx_new_image(mlx.ptr, SCREENW, SCREENH);
	text.texture1 = mlx_xpm_file_to_image(mlx.ptr, "textures/cat1.xpm", &(text.text1_w), &(text.text1_h));
	text.texture2 = mlx_xpm_file_to_image(mlx.ptr, "textures/cat2.xpm", &(text.text2_w), &(text.text2_h));
	text.texture3 = mlx_xpm_file_to_image(mlx.ptr, "textures/cat3.xpm", &(text.text3_w), &(text.text3_h));
	text.texture4 = mlx_xpm_file_to_image(mlx.ptr, "textures/cat4.xpm", &(text.text4_w), &(text.text4_h));
	text.texture1_data = (int *)mlx_get_data_addr(text.texture1, &text.text1_sizebit, &text.text1_sizeline, &text.text1_endian);
	text.texture2_data = (int *)mlx_get_data_addr(text.texture2, &text.text2_sizebit, &text.text2_sizeline, &text.text2_endian);
	text.texture3_data = (int *)mlx_get_data_addr(text.texture3, &text.text3_sizebit, &text.text3_sizeline, &text.text3_endian);
	text.texture4_data = (int *)mlx_get_data_addr(text.texture4, &text.text4_sizebit, &text.text4_sizeline, &text.text4_endian);
	mlx.data_addr = (int *)mlx_get_data_addr(mlx.img, &(mlx.bits), &(mlx.size_line), &(mlx.endian));
	mlx_hook(mlx.win, 2, 1, movement, (void *)&params);
	mlx_loop_hook ( mlx.ptr, run_game, (void *)&params);
	mlx_loop(mlx.ptr);
}
