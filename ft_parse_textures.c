/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:17:59 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/20 14:46:31 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	check_txt(int dir, t_param *p)
{
	if (dir == 1)
	{
		if (p->t1_done)
			put_error("ERROR\nNORTH Texture set more than once\n", p);
		else
			p->t1_done = 1;
	}
	if (dir == 2)
	{
		if (p->t2_done)
			put_error("ERROR\nSOUTH Texture set more than once\n", p);
		else
			p->t2_done = 1;
	}
	if (dir == 3)
	{
		if (p->t3_done)
			put_error("ERROR\nWEST Texture set more than once\n", p);
		else
			p->t3_done = 1;
	}
	if (dir == 4)
	{
		if (p->t4_done)
			put_error("ERROR\nEAST Texture set more than once\n", p);
		else
			p->t4_done = 1;
	}
	if (dir == 5)
	{
		if (p->spr_done)
			put_error("ERROR\nSPRITE Texture set more than once\n", p);
		else
			p->spr_done = 1;
	}
}

void	make_txt(int dir, char *str, t_param *p)
{
	while (*str == ' ')
		str++;
	if (dir == 1)
		p->mlx->txt->txt1_path = ft_strdup(str);
	if (dir == 2)
		p->mlx->txt->txt2_path = ft_strdup(str);
	if (dir == 3)
		p->mlx->txt->txt3_path = ft_strdup(str);
	if (dir == 4)
		p->mlx->txt->txt4_path = ft_strdup(str);
	if (dir == 5)
		p->mlx->txt->spr_path = ft_strdup(str);
	check_txt(dir, p);
}