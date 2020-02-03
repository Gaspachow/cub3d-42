/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:06:04 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/03 13:38:49 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		rgb_int(int red, int green, int blue)
{
	int	rgb;

	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

void	drawsprite(t_mlx *mlx, int x)
{
	int		i;
	double	pos;
	double	step;
	int		*text;

	step = 1.0 * mlx->txt->text5_h / mlx->spr_l;
	pos = (mlx->spr_start - mlx->screen_h / 2 + mlx->spr_l / 2) * step;
	i = mlx->spr_start;
	text = mlx->txt->txt5_data;
	while (i < mlx->spr_end)
	{
		*(mlx->d_ad + x + i++ * mlx->sl / 4) = *(text + mlx->sprite_x +
		(int)pos * mlx->txt->text5_sl / 4);
		pos += step;
	}
	mlx->sprite_x++;
}

int		drawline(t_mlx *mlx, int x, int text_x)
{
	int		i;
	int		*text;
	double	step;
	double	pos;

	i = -1;
	step = 1.0 * mlx->text_h / mlx->l_height;
	pos = (mlx->l_start - mlx->screen_h / 2 + mlx->l_height / 2) * step;
	text = mlx->txt_data;
	while (++i < mlx->l_start)
	{
		*(mlx->d_ad + x + i * mlx->sl / 4) = rgb_int(135, 197, 214);
	}
	while (i < mlx->l_end)
	{
		*(mlx->d_ad + x + i++ * mlx->sl / 4) = *(text + text_x +
		(int)pos * mlx->text_sl / 4);
		pos += step;
	}
	while (i < mlx->screen_h)
		*(mlx->d_ad + x + i++ * mlx->sl / 4) = rgb_int(125, 125, 125);
	return (1);
}

void	define_line(t_mlx *mlx, t_ray *ray)
{
	mlx->l_height = (int)(mlx->screen_h / ray->walldist);
	mlx->l_start = (mlx->l_height * -1) / 2 + mlx->screen_h / 2;
	if (mlx->l_start < 0)
		mlx->l_start = 0;
	mlx->l_end = mlx->l_height / 2 + mlx->screen_h / 2;
	if (mlx->l_end >= mlx->screen_h)
		mlx->l_end = mlx->screen_h - 1;
}

void	define_sprite_line(t_mlx *mlx, t_ray *ray)
{
	mlx->spr_l = (int)(mlx->screen_h / ray->spritedist);
	mlx->spr_start = (mlx->spr_l * -1) / 2 + mlx->screen_h / 2;
	if (mlx->spr_start < 0)
		mlx->spr_start = 0;
	mlx->spr_end = mlx->spr_l / 2 + mlx->screen_h / 2;
	if (mlx->spr_end >= mlx->screen_h)
		mlx->spr_end = mlx->screen_h - 1;
}

void	choose_texture(t_mlx *mlx, t_ray *ray)
{
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
}
