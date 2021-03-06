/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:56:41 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/21 14:59:26 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	txt_init(t_txt *text, t_mlx *mlx)
{
	text->txt1 = mlx_xpm_file_to_image(mlx->ptr,
	text->txt1_path, &(text->text1_w), &(text->text1_h));
	text->txt2 = mlx_xpm_file_to_image(mlx->ptr,
	text->txt2_path, &(text->text2_w), &(text->text2_h));
	text->txt3 = mlx_xpm_file_to_image(mlx->ptr,
	text->txt3_path, &(text->text3_w), &(text->text3_h));
	text->txt4 = mlx_xpm_file_to_image(mlx->ptr,
	text->txt4_path, &(text->text4_w), &(text->text4_h));
	text->txt5 = mlx_xpm_file_to_image(mlx->ptr,
	text->spr_path, &(text->text5_w), &(text->text5_h));
	text->txt1_data = (int *)mlx_get_data_addr(text->txt1,
	&text->text1_sb, &text->text1_sl, &text->text1_ed);
	text->txt2_data = (int *)mlx_get_data_addr(text->txt2,
	&text->text2_sb, &text->text2_sl, &text->text2_ed);
	text->txt3_data = (int *)mlx_get_data_addr(text->txt3,
	&text->text3_sb, &text->text3_sl, &text->text3_ed);
	text->txt4_data = (int *)mlx_get_data_addr(text->txt4,
	&text->text4_sb, &text->text4_sl, &text->text4_ed);
	text->txt5_data = (int *)mlx_get_data_addr(text->txt5,
	&text->text5_sb, &text->text5_sl, &text->text5_ed);
}

void	set_camerans(char dir, t_player *pl)
{
	if (dir == 'N')
	{
		pl->dir_x = -1;
		pl->dir_y = 0;
		pl->plane_x = 0;
		pl->plane_y = 0.66;
	}
	else if (dir == 'S')
	{
		pl->dir_x = 1;
		pl->dir_y = 0;
		pl->plane_x = 0;
		pl->plane_y = -0.66;
	}
}

void	set_cameraew(char dir, t_player *pl)
{
	if (dir == 'W')
	{
		pl->dir_x = 0;
		pl->dir_y = -1;
		pl->plane_x = -0.66;
		pl->plane_y = 0;
	}
	else if (dir == 'E')
	{
		pl->dir_x = 0;
		pl->dir_y = 1;
		pl->plane_x = 0.66;
		pl->plane_y = 0;
	}
}

int		player_init(int x, int y, char dir, t_param *p)
{
	if (dir != 'N' && dir != 'S' && dir != 'E' && dir != 'W')
		put_error("ERROR: INVALID MAP ITEM\n", p);
	if (p->pl->pos > 0)
		put_error("ERROR: MULTIPLE SPAWNPOINTS SET\n", p);
	p->pl->pos_x = x + 0.5;
	p->pl->pos_y = y + 0.5;
	if (dir == 'N' || dir == 'S')
		set_camerans(dir, p->pl);
	else
		set_cameraew(dir, p->pl);
	p->pl->forward = 0;
	p->pl->backward = 0;
	p->pl->left = 0;
	p->pl->right = 0;
	p->pl->rightrot = 0;
	p->pl->leftrot = 0;
	return (1);
}
