/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:24:08 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/19 21:31:33 by gsmets           ###   ########.fr       */
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

int	make_resolution(char c, char *str, t_param *p)
{
	return (1);
}

int	choose_param(char c, char *str, t_param *p)
{
	if (c == 'R')
		make_resolution(c, str, p);
	if (c == '1' || c == '0' || c == '2')
		return (0);
	return (1);
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
	put_error("ERROR: NO MAP FOUND", p);
	return (lines);
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
	maplines = parse_parameters(p, lines);
	parse_map(p, maplines);
	free(lines);
	p->mlx->sprites = get_sprites(p);
	p->mlx->sprite_hit = 0;
	return (1);
}
