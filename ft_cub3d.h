/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:13:22 by gsmets            #+#    #+#             */
/*   Updated: 2020/01/28 15:27:15 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# define MAPW 24
# define MAPH 24
# define SCREENW 640
# define SCREENH 480

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

int		rgb_int(int red, int green, int blue);
int		drawline(t_mlx *mlx, int x, int text_x);
void	player_init(t_player *pl);
void	get_step(t_world *map, t_ray *ray, t_player *pl);
void	raycast(t_player *pl, t_mlx *mlx, t_world *map, t_ray *ray);
void	rotation(int key, t_player *pl);
void	mov_updown(int key, t_player *pl, t_world *map, float speed);
void	mov_leftright(int key, t_player *pl, t_world *map, float speed);
int		key_input(int key, t_param *params);
int		run_game(t_param *params);
void	txt_init(t_txt *text, t_mlx *mlx);

#endif