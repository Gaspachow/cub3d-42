/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:56:41 by gsmets            #+#    #+#             */
/*   Updated: 2020/01/30 14:27:06 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

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

void	player_init(t_player *pl)
{
	pl->pos_x = 22;
	pl->pos_y = 10;
	pl->dir_x = -1;
	pl->dir_y = 0;
	pl->plane_x = 0;
	pl->plane_y = 0.66;
	pl->forward = 0;
	pl->backward = 0;
	pl->left = 0;
	pl->right = 0;
	pl->rightrot = 0;
	pl->leftrot = 0;
}
