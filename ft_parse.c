/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:24:08 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/20 18:43:53 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

char	**get_lines(char **lines, char **tmp, int fd)
{
	char	*s;
	int		i;
	int		j;
	int		ret;

	ret = 1;
	i = 1;
	while (ret)
	{
		ret = get_next_line(fd, &s);
		tmp = lines;
		j = 0;
		lines = malloc((i + 1) * sizeof(char *));
		if (tmp)
			while (tmp[j])
			{
				lines[j] = tmp[j];
				j++;
			}
		free(tmp);
		lines[j++] = s;
		lines[j] = 0;
		i++;
	}
	return (lines);
}

char	**parse_parameters(t_param *p, char **lines)
{
	int i;
	int j;
	int map;

	i = 0;
	map = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j] == ' ')
			j++;
		if (!choose_param(lines[i][j], lines[i], p))
		{
			return(&lines[i]);
		}
		i++;
	}
	put_error("ERROR\nNO MAP FOUND\n", p);
	return (lines);
}

void	init_params(t_param *p)
{
	p->screen_done = 0;
	p->floor_done = 0;
	p->mlx->fr = -1;
	p->mlx->fg = -1;
	p->mlx->fb = -1;
	p->mlx->sr = -1;
	p->mlx->sg = -1;
	p->mlx->sb = -1;
	p->t1_done = 0;
	p->t2_done = 0;
	p->t3_done = 0;
	p->t4_done = 0;
	p->spr_done = 0;
}

void	verify_params(t_param *p)
{
	if (!(p->screen_done))
		put_error("ERROR\nNO RESOLUTION INPUT\n", p);
	if (!(p->floor_done))
		put_error("ERROR\nNO FLOOR COLOR INPUT\n", p);
	if (!(p->sky_done))
		put_error("ERROR\nNO CEILING COLOR INPUT\n", p);
	if (!p->t1_done || !p->t2_done || !p->t3_done || !p->t4_done || !p->spr_done)
		put_error("ERROR\nMISSING TEXTURE PATH\n", p);
}

int		parse_cub(char *fname, t_param *p)
{
	int		fd;
	char	**tmp;
	char	**maplines;

	fd = open(fname, O_RDONLY);
	p->lines = 0;
	p->lines = get_lines(p->lines, tmp, fd);
	close(fd);
	init_params(p);
	maplines = parse_parameters(p, p->lines);
	verify_params(p);
	parse_map(p, maplines);
	p->mlx->sprites = get_sprites(p);
	p->mlx->sprite_hit = 0;
	return (1);
}
