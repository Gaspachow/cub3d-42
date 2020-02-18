/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:24:08 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/18 14:27:11 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		fill_map(char **lines, int fd, t_param *p)
{
	p->i = 0;
	p->j = 0;
	while (lines[p->i])
	{
		p->map->worldmap[p->i] = malloc((ft_strlen(lines[p->i]) + 1) *
		sizeof(int *));
		p->j = 0;
		while (lines[p->i][p->j])
		{
			if (lines[p->i][p->j] > '2' || lines[p->i][p->j] < '0')
			{
				player_init(p->i, p->j, lines[p->i][p->j], p);
				p->map->worldmap[p->i][p->j] = 0;
			}
			else
				p->map->worldmap[p->i][p->j] = lines[p->i][p->j] - '0';
			p->j++;
		}
		p->map->worldmap[p->i][p->j] = -1;
		free(lines[p->i]);
		p->i++;
	}
	close(fd);
	return (1);
}

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
	return (j);
}

int		parse_cub(char *fname, t_param *p)
{
	int		fd;
	int		j;
	char	**tmp;
	char	**lines;

	fd = open(fname, O_RDONLY);
	lines = 0;
	j = get_lines(&lines, &tmp, fd);
	p->map->worldmap = malloc(j * sizeof(int *));
	p->map->worldmap[j] = 0;
	fill_map(lines, fd, p);
	return (1);
}
