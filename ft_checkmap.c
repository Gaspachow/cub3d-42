/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:31:02 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/18 19:53:59 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		checkmap(t_param *p, int x, int y)
{
	int check;
	int	**map;

	check = 0;
	map = p->map->worldmap;

	if (map[x][y] == 1 || map[x][y] == 3 || map[x][y] == 4)
		return(1);
	if (x == 0 || y == 0 || x == p->map->max_x)
		return (0);
	if (map[x][y] == -1)
		return(0);
	if (map[x][y] == 0)
		map[x][y] = 3;
	if (map[x][y] == 2)
		map[x][y] = 4;
	check += checkmap(p, x + 1, y);
	check += checkmap(p, x, y + 1);
	check += checkmap(p, x - 1, y);
	check += checkmap(p, x, y - 1);
	if (check != 4)
		return (0);
	return (1);
}