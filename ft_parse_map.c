/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:40:02 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/19 18:57:18 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	make_map(char **lines, t_world *map, t_param *p)
{
	int		i;
	int		j;
	int		x;
	int		y;

	x = 0;
	i = 0;
	while (lines[i])
	{
		y = 0;
		j = 0;
		while (lines[i][j])
		{
			while(lines[i][j] == ' ')
				j++;
			map->worldmap[x][y++] = lines[i][j++] - '0';
		}
		j = 0;
		free(lines[i]);
		i++;
		x++;
	}
}

int		get_max_x(char **lines)
{
	int i;

	i = 0;
	while (lines[i])
		i++;
	return (i);
}

int		get_max_y(char **lines)
{
	int i;
	int j;
	int len;
	int biglen;

	i = 0;
	j = 0;
	biglen = 0;
	while (lines[i])
	{
		len = 0;
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] != ' ')
				len++;
			j++;
		}
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

int		check_mapvalue(int value, int x, int y, t_param *p)
{
	if (value == 35 || value == 21 || value == 39 || value == 30)
	{
		player_init(x, y, (value + 48), p);
		return (1);
	}
	return (0);
}

void	check_player(t_param *p)
{
	int	i;
	int	j;
	int done;

	i = 0;
	done = 0;
	while(i <= p->map->max_x && !done)
	{
		j = 0;
		while (j <= p->map->max_y && !done)
		{
			done = check_mapvalue(p->map->worldmap[i][j], i, j, p);
			j++;
		}
		i++;
	}
}

void	parse_map(t_param *p, char **maplines)
{
	p->map->max_x = get_max_x(maplines);
	p->map->max_y = get_max_y(maplines);
	init_map(p->map);
	make_map(maplines, p->map, p);
	free(maplines);
	check_player(p);
	checkmap(p, p->pl->pos_x, p->pl->pos_y);
}
