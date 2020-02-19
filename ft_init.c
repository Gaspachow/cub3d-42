/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:56:41 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/19 13:44:48 by gsmets           ###   ########.fr       */
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
	text->txt5 = mlx_xpm_file_to_image(mlx->ptr,
	"textures/barrel.xpm", &(text->text5_w), &(text->text5_h));
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

void	set_cameraNS(char dir, t_player *pl)
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

void	set_cameraEW(char dir, t_player *pl)
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
	p->pl->pos_x = x + 0.5;
	p->pl->pos_y = y + 0.5;
	if (dir == 'N' || dir == 'S')
		set_cameraNS(dir, p->pl);
	else if (dir == 'E' || dir == 'W')
		set_cameraEW(dir, p->pl);
	else
		return (EXIT_FAILURE);
	p->pl->forward = 0;
	p->pl->backward = 0;
	p->pl->left = 0;
	p->pl->right = 0;
	p->pl->rightrot = 0;
	p->pl->leftrot = 0;
	return(1);
}
