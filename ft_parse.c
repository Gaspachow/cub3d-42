/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:24:08 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/19 15:41:19 by gsmets           ###   ########.fr       */
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

int		parse_cub(char *fname, t_param *p)
{
	int		fd;
	char	**tmp;
	char	**lines;

	fd = open(fname, O_RDONLY);
	lines = 0;
	get_lines(&lines, &tmp, fd);
	p->map->max_x = get_map(lines, p->map);
	p->map->max_y = get_max_y(lines);
	init_map(p->map);
	fill_map(lines, fd, p);
	free(lines);
	close(fd);
	if (!(checkmap(p, p->pl->pos_x, p->pl->pos_y)))
		put_error("ERROR: MAP NOT CLOSED\n", p);
	p->mlx->sprites = get_sprites(p);
	p->mlx->sprite_hit = 0;
	return (1);
}
