/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:31:02 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/19 20:39:52 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	checkmap(t_param *p, int x, int y)
{
	int	**map;

	p->pl->pos = 0;
	map = p->map->worldmap;
	if (map[x][y] == 1 || map[x][y] == 3 || map[x][y] == 4)
		return ;
	if (x == 0 || y == 0 || x == p->map->max_x)
		put_error("ERROR: MAP NOT CLOSED AROUND SPAWN\n", p);
	if (map[x][y] == -1)
		put_error("ERROR: MAP NOT CLOSED AROUND SPAWN\n", p);
	if (map[x][y] == 0)
		map[x][y] = 3;
	if (map[x][y] == 2)
		map[x][y] = 4;
	checkmap(p, x + 1, y);
	checkmap(p, x, y + 1);
	checkmap(p, x - 1, y);
	checkmap(p, x, y - 1);
}
