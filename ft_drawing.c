/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:06:04 by gsmets            #+#    #+#             */
/*   Updated: 2020/01/28 15:16:46 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	rgb_int(int red, int green, int blue)
{
	int	rgb;

	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

int	drawline(t_mlx *mlx, int x, int text_x)
{
	int		i;
	int		*text;
	double	step;
	double	pos;

	i = -1;
	step = 1.0 * mlx->text_h / mlx->l_height;
	pos = (mlx->l_start - SCREENH / 2 + mlx->l_height / 2) * step;
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
	while (i < SCREENH)
	{
		*(mlx->d_ad + x + i++ * mlx->sl / 4) = rgb_int(125, 125, 125);
	}
	return (1);
}
