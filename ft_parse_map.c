/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:40:02 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/19 15:40:57 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		fill_map(char **lines, int fd, t_param *p)
{
	p->i = 0;
	while (lines[p->i])
	{
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
		free(lines[p->i]);
		p->i++;
	}
	return (1);
}

int		get_map(char **lines, t_world *map)
{
	int		i;
	int		j;
	int		x;
	int		y;

	x = 0;
	i = 0;
	j = 0;
	while (lines[i][j] != '\n')
	{
		y = 0;
		while (lines[i][j])
			if (lines[i][j] != ' ')
				map->worldmap[x][y++] = lines[i][j] - '0';
		i++;
		j = 0;
	}
	return (i - 1);
}

int		get_max_y(char **lines)
{
	int i;
	int len;
	int biglen;

	i = 0;
	biglen = 0;
	while (lines[i])
	{
		len = ft_strlen(lines[i]);
		if (len > biglen)
			biglen = len;
		i++;
	}
	return (biglen);
}

void	init_map(t_world *map)
{
	int i;
	int j;

	i = 0;
	map->worldmap = malloc((map->max_x + 1) * sizeof(int *));
	while (i <= map->max_x)
	{
		map->worldmap[i] = malloc((map->max_y + 1) * sizeof(int));
		j = 0;
		while (j <= map->max_y)
		{
			map->worldmap[i][j] = 8;
			j++;
		}
		i++;
	}
}
