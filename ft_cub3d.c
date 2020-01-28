/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:43:55 by gsmets            #+#    #+#             */
/*   Updated: 2020/01/28 13:37:07 by gsmets           ###   ########.fr       */
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

typedef	struct		s_txt
{
	void			*txt1;
	int				*txt1_data;
	int				text1_h;
	int				text1_w;
	int				text1_sl;
	int				text1_sb;
	int				text1_ed;
	void			*txt2;
	int				*txt2_data;
	int				text2_h;
	int				text2_w;
	int				text2_sl;
	int				text2_sb;
	int				text2_ed;
	void			*txt3;
	int				*txt3_data;
	int				text3_h;
	int				text3_w;
	int				text3_sl;
	int				text3_sb;
	int				text3_ed;
	void			*txt4;
	int				*txt4_data;
	int				text4_h;
	int				text4_w;
	int				text4_sl;
	int				text4_sb;
	int				text4_ed;
}					t_txt;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	void			*img;
	int				*d_ad;
	int				bits;
	int				sl;
	int				ed;
	int				l_height;
	int				l_start;
	int				l_end;
	int				color;
	t_txt			*txt;
	int				*txt_data;
	int				text_sl;
	int				text_h;
	int				text_x;

}					t_mlx;

typedef struct		s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
}					t_player;

typedef struct		s_world
{
	double			time;
	double			oldtime;
	int				x;
	int				y;
	int				step_x;
	int				step_y;
}					t_world;

typedef struct		s_ray
{
	double			dir_x;
	double			dir_y;
	double			side_x;
	double			side_y;
	double			delta_x;
	double			delta_y;
	double			walldist;
}					t_ray;

typedef struct		s_param
{
	t_mlx			*mlx;
	t_player		*pl;
	t_world			*map;
	t_ray			*ray;
}					t_param;

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

int drawline(t_mlx *mlx, int x, int text_x)
{
	int i;
	int *text;
	double step;

	i = 0;
	step = 1.0 * mlx->text_h / mlx->l_height;
	double pos = (mlx->l_start - SCREENH / 2 + mlx->l_height / 2) * step;
	text = mlx->txt_data;
	while (i < mlx->l_start)
	{
		*(mlx->d_ad + x + i * mlx->sl / 4) = rgb_int(135, 197, 214);
		i++;
	}

	while (i < mlx->l_end)
	{
		*(mlx->d_ad + x + i * mlx->sl / 4) = *(text + text_x + (int)pos * mlx->text_sl / 4);
		i++;
		pos += step;
	}

	while (i < SCREENH)
	{
		*(mlx->d_ad + x + i * mlx->sl / 4) = rgb_int(125, 125, 125);
		i++;
	}
	return (1);
}

void	player_init(t_player *pl)
{
	pl->pos_x = 22;
	pl->pos_y = 10;
	pl->dir_x = -1;
	pl->dir_y = 0;
	pl->plane_x = 0;
	pl->plane_y = 0.66;
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
		// mlx->text_x = (mlx->text_sl / 4) - mlx->text_x - 1;
		// if (side == 0 && ray->dir_x > 0)
		// 	mlx->text_x = (mlx->text_sl / 4) - mlx->text_x -1;
		// else if (side == 1 && ray->dir_y < 0)
		// 	mlx->text_x = (mlx->text_sl / 4) - mlx->text_x -1;
		// wallx -= floor(wallx);
		// mlx->text_x = wallx * mlx->text_sl / 4;

		drawline(mlx, x, mlx->text_x);
		x++;
	}
}

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

int		run_game(t_param *params)
{
	t_mlx		*mlx;
	t_player	*pl;
	t_world		*map;
	t_ray		*ray;

	mlx = params->mlx;
	pl = params->pl;
	map = params->map;
	ray = params->ray;
	raycast(pl, mlx, map, ray);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	return (0);
}


void	txt_init(t_txt *text, t_mlx *mlx)
{
	text->txt1 = mlx_xpm_file_to_image(mlx->ptr,
	"textures/cat1.xpm", &(text->text1_w), &(text->text1_h));
	text->txt2 = mlx_xpm_file_to_image(mlx->ptr,
	"textures/cat2.xpm", &(text->text2_w), &(text->text2_h));
	text->txt3 = mlx_xpm_file_to_image(mlx->ptr,
	"textures/cat3.xpm", &(text->text3_w), &(text->text3_h));
	text->txt4 = mlx_xpm_file_to_image(mlx->ptr,
	"textures/cat4.xpm", &(text->text4_w), &(text->text4_h));
	text->txt1_data = (int *)mlx_get_data_addr(text->txt1,
	&text->text1_sb, &text->text1_sl, &text->text1_ed);
	text->txt2_data = (int *)mlx_get_data_addr(text->txt2,
	&text->text2_sb, &text->text2_sl, &text->text2_ed);
	text->txt3_data = (int *)mlx_get_data_addr(text->txt3,
	&text->text3_sb, &text->text3_sl, &text->text3_ed);
	text->txt4_data = (int *)mlx_get_data_addr(text->txt4,
	&text->text4_sb, &text->text4_sl, &text->text4_ed);
}


int		main()
{
	t_mlx		mlx;
	t_player	one;
	t_world		map;
	t_ray		ray;
	t_param		params;
	t_txt	text;

	params.mlx = &mlx;
	params.pl = &one;
	params.map = &map;
	params.ray = &ray;
	mlx.txt = &text;
	player_init(&one);
	if (!(mlx.ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(mlx.win = mlx_new_window(mlx.ptr, SCREENW, SCREENH, "cub3d")))
		return (EXIT_FAILURE);
	mlx.img = mlx_new_image(mlx.ptr, SCREENW, SCREENH);
	txt_init(&text, &mlx);
	mlx.d_ad = (int *)mlx_get_data_addr(mlx.img, &(mlx.bits), &(mlx.sl), &(mlx.ed));
	mlx_hook(mlx.win, 2, 1, key_input, (void *)&params);
	mlx_loop_hook ( mlx.ptr, run_game, (void *)&params);
	mlx_loop(mlx.ptr);
}
