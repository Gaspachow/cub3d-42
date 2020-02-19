/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:24:08 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/19 13:45:22 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		fill_map(char **lines, int fd, t_param *p)
{
	p->i = 0;
	p->j = 0;
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
	free(lines);
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
		ret = gnl_space(fd, &s);
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
	return (i);
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

int		count_sprites(t_world *map)
{
	int x;
	int y;
	int count;

	x = 0;
	while (x < map->max_x)
	{
		y = 0;
		while (y < map->max_y)
		{
			if (map->worldmap[x][y] == 4)
				count++;
			y++;
		}
		x++;
	}
	return (count);
}

t_spriteptr	*get_sprites(t_param *p)
{
	t_spriteptr *sprites;
	int x;
	int y;
	int i;

	p->mlx->spr_number = count_sprites(p->map);
	sprites = (malloc(p->mlx->spr_number * sizeof(t_spriteptr)));
	p->mlx->spr_order = (malloc(p->mlx->spr_number * sizeof(int)));
	x = 0;
	i = 0;
	while (x < p->map->max_x)
	{
		y = 0;
		while (y < p->map->max_y)
		{
			if (p->map->worldmap[x][y] == 4)
				{
					sprites[i].x = x;
					sprites[i++].y = y;
				}
			y++;
		}
		x++;
	}
	return (sprites);
}

int		parse_cub(char *fname, t_param *p)
{
	int		fd;
	char	**tmp;
	char	**lines;

	fd = open(fname, O_RDONLY);
	lines = 0;
	p->map->max_x = get_lines(&lines, &tmp, fd) - 1;
	p->map->max_y = get_max_y(lines);
	init_map(p->map);
	fill_map(lines, fd, p);
	if (!(checkmap(p, p->pl->pos_x, p->pl->pos_y)))
	{
		write(1, "ERROR: MAP UNCLOSED\n", 20);
		exit(EXIT_FAILURE);
	}
	p->mlx->sprites = get_sprites(p);
	p->mlx->sprite_hit = 0;
	return (1);
}
