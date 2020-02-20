/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:24:08 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/20 13:50:54 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		get_lines(char ***lines, char ***tmp, int fd)
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
		(*tmp) = (*lines);
		j = 0;
		(*lines) = malloc((i + 1) * sizeof(char *));
		if ((*tmp))
			while ((*tmp)[j])
			{
				(*lines)[j] = (*tmp)[j];
				j++;
			}
		free((*tmp));
		(*lines)[j++] = s;
		(*lines)[j] = 0;
		i++;
	}
	return (i - 1);
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
	put_error("ERROR: NO MAP FOUND\n", p);
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
}

void	verify_params(t_param *p)
{
	if (!(p->screen_done))
		put_error("ERROR: NO RESOLUTION INPUT\n", p);
	if (!(p->floor_done))
		put_error("ERROR: NO FLOOR COLOR INPUT\n", p);
	if (!(p->sky_done))
		put_error("ERROR: NO CEILING COLOR INPUT\n", p);
}

int		parse_cub(char *fname, t_param *p)
{
	int		fd;
	char	**tmp;
	char	**lines;
	char	**maplines;

	fd = open(fname, O_RDONLY);
	lines = 0;
	get_lines(&lines, &tmp, fd);
	close(fd);
	init_params(p);
	maplines = parse_parameters(p, lines);
	verify_params(p);
	parse_map(p, maplines);
	free(lines);
	p->mlx->sprites = get_sprites(p);
	p->mlx->sprite_hit = 0;
	return (1);
}
