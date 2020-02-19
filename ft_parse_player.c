/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 20:15:56 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/19 20:42:24 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		check_mapvalue(int value, int x, int y, t_param *p)
{
	if (value != 1 && value != 2 && value != 0 && value != -1)
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

	i = 0;
	p->pl->pos = 0;
	while (i <= p->map->max_x)
	{
		j = 0;
		while (j <= p->map->max_y)
		{
			p->pl->pos += check_mapvalue(p->map->worldmap[i][j], i, j, p);
			j++;
		}
		i++;
	}
	if (p->pl->pos == 0)
		put_error("ERROR: NO SPAWNPOINT\n", p);
}
