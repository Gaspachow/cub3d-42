/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:05:55 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/20 20:07:14 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	extra_error(char *str, t_param *p, char *message)
{
	while (ft_isdigit(*str))
		str++;
	while (*str == ' ')
		str++;
	if (*str)
		put_error(message, p);
}

void	make_resolution(char *str, t_param *p)
{
	if (p->screen_done)
		put_error("ERROR\nMultiple resolution inputs\n", p);
	p->screen_done = 1;
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
	extra_error(str, p, "ERROR\nToo many resolution inputs");
	if (p->mlx->screen_h <= 0 || p->mlx->screen_w <= 0)
		put_error("ERROR\nIncorrect resolution values\n", p);
	p->mlx->screen_h = (p->mlx->screen_h > 1440 ? 1440 : p->mlx->screen_h);
	p->mlx->screen_w = (p->mlx->screen_w > 2560 ? 2560 : p->mlx->screen_w);
}

void	make_floor(char *str, t_param *p)
{
	if (p->floor_done)
		put_error("ERROR\nMultiple floor color inputs\n", p);
	while (*str == ' ')
		str++;
	p->mlx->fr = ft_cubatoi_f(str);
	while (ft_isdigit(*str) || *str == ' ')
		str++;
	if (*(str++) != ',')
		put_error("ERROR\nWrong floor color input\n", p);
	while (*str == ' ')
		str++;
	p->mlx->fg = ft_cubatoi_f(str);
	while (ft_isdigit(*str) || *str == ' ')
		str++;
	if (*(str++) != ',')
		put_error("ERROR\nWrong floor color input\n", p);
	while (*str == ' ')
		str++;
	p->mlx->fb = ft_cubatoi_f(str);
	if (p->mlx->fb == -1 || p->mlx->fr == -1 || p->mlx->fg == -1)
		put_error("ERROR\nWrong values for floor color\n", p);
	extra_error(str, p, "ERROR\nToo many resolution inputs");
	p->floor_done = 1;
}

void	make_sky(char *str, t_param *p)
{
	if (p->sky_done)
		put_error("ERROR\nMultiple ceiling color inputs\n", p);
	while (*str == ' ')
		str++;
	p->mlx->sr = ft_cubatoi_f(str);
	while (ft_isdigit(*str) || *str == ' ')
		str++;
	if (*(str++) != ',')
		put_error("ERROR\nWrong ceiling color input\n", p);
	while (*str == ' ')
		str++;
	p->mlx->sg = ft_cubatoi_f(str);
	while (ft_isdigit(*str) || *str == ' ')
		str++;
	if (*(str++) != ',')
		put_error("ERROR\nWrong ceiling color input\n", p);
	while (*str == ' ')
		str++;
	p->mlx->sb = ft_cubatoi_f(str);
	while (ft_isdigit(*str) || *str == ' ')
		str++;
	if (*str || p->mlx->sb == -1 || p->mlx->sr == -1 || p->mlx->sg == -1)
		put_error("ERROR\nWrong values for ceiling color\n", p);
	p->sky_done = 1;
}

int		choose_param(char c, char *str, t_param *p)
{
	if (c == 'R' && *(str + 1) == ' ')
		make_resolution(str + 1, p);
	else if (c == 'F' && *(str + 1) == ' ')
		make_floor(str + 1, p);
	else if (c == 'C' && *(str + 1) == ' ')
		make_sky(str + 1, p);
	else if (c == 'N' && *(str + 1) == 'O' && *(str + 2) == ' ')
		make_txt(1, str + 2, p);
	else if (c == 'S' && *(str + 1) == 'O' && *(str + 2) == ' ')
		make_txt(2, str + 2, p);
	else if (c == 'W' && *(str + 1) == 'E' && *(str + 2) == ' ')
		make_txt(4, str + 2, p);
	else if (c == 'E' && *(str + 1) == 'A' && *(str + 2) == ' ')
		make_txt(3, str + 2, p);
	else if (c == 'S' && *(str + 1) == ' ')
		make_txt(5, str + 1, p);
	else if (c == '1' || c == '0' || c == '2')
		return (0);
	else if (c)
		put_error("ERROR\nNON-EMPTY LINE WITH WRONG IDENTIFIER\n", p);
	return (1);
}
