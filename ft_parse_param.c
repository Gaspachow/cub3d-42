/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:05:55 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/20 13:40:42 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	make_resolution(char *str, t_param *p)
{
	str++;
	if (p->screen_done)
		put_error("ERROR\nMultiple resolution inputs\n", p);
	p->screen_done = 1;
	if (*str != ' ')
		put_error("ERROR\nWrong resolution input\n", p);
	while (*str == ' ')
		str++;
	p->mlx->screen_w = ft_cubatoi_r(&(*str));
	while (ft_isdigit(*str))
		str++;
	if (*str != ' ')
		put_error("ERROR\nWrong height input\n", p);
	while (*str == ' ')
		str++;
	p->mlx->screen_h = ft_cubatoi_r(str);
	if (p->mlx->screen_h <= 0 || p->mlx->screen_w <= 0)
		put_error("ERROR\nIncorrect resolution values\n", p);
	p->mlx->screen_h = (p->mlx->screen_h > 1440 ? 1440 : p->mlx->screen_h);
	p->mlx->screen_w = (p->mlx->screen_w > 2560 ? 2560 : p->mlx->screen_w);
}

void	make_floor(char *str, t_param *p)
{
	str++;
	if (*str != ' ')
		put_error("ERROR\nWrong floor color input\n", p);
	while (*str == ' ')
		str++;
	p->mlx->fr = ft_cubatoi_f(str);
	while (ft_isdigit(*str))
		str++;
	if (*(str++) != ',')
		put_error("ERROR\nWrong floor color input\n", p);
	while (*str == ' ')
		str++;
	p->mlx->fg = ft_cubatoi_f(str);
	while (ft_isdigit(*str))
		str++;
	if (*(str++) != ',')
		put_error("ERROR\nWrong floor color input\n", p);
	while (*str == ' ')
		str++;
	p->mlx->fb = ft_cubatoi_f(str);
	if (p->mlx->fb == -1 || p->mlx->fr == -1 || p->mlx->fg == -1)
		put_error("ERROR\nWrong values for floor color\n", p);
	p->floor_done = 1;
}

void	make_sky(char *str, t_param *p)
{
	str++;
	if (*str != ' ')
		put_error("ERROR\nWrong ceiling color input\n", p);
	while (*str == ' ')
		str++;
	p->mlx->sr = ft_cubatoi_f(str);
	while (ft_isdigit(*str))
		str++;
	if (*(str++) != ',')
		put_error("ERROR\nWrong ceiling color input\n", p);
	while (*str == ' ')
		str++;
	p->mlx->sg = ft_cubatoi_f(str);
	while (ft_isdigit(*str))
		str++;
	if (*(str++) != ',')
		put_error("ERROR\nWrong ceiling color input\n", p);
	while (*str == ' ')
		str++;
	p->mlx->sb = ft_cubatoi_f(str);
	if (p->mlx->sb == -1 || p->mlx->sr == -1 || p->mlx->sg == -1)
		put_error("ERROR\nWrong values for ceiling color\n", p);
	p->sky_done = 1;
}

int		choose_param(char c, char *str, t_param *p)
{
	if (c == 'R')
		make_resolution(str, p);
	if (c == 'F')
		make_floor(str, p);
	if (c == 'C')
		make_sky(str, p);
	if (c == '1' || c == '0' || c == '2')
		return (0);
	return (1);
}