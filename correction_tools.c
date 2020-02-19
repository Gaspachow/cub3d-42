/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correction_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 11:41:48 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/19 11:47:03 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	print_map(t_world *map)
{
	int x;
	int y;
	x = 0;
	y = 0;
	while (x <= map->max_x)
	{
		y = 0;
		while (y <= map->max_y)
		{
			ft_putnbr(map->worldmap[x][y]);
			write(1, " ", 1);
			y++;
		}
		x++;
		write(1, "\n", 1);
	}
	write(1, "\n-----------------\n", 19);
}
