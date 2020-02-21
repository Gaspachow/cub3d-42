/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keypress.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:03:24 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/21 15:03:49 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		key_press(int key, t_param *p)
{
	if (key == 1)
		p->pl->backward = 1;
	else if (key == 13)
		p->pl->forward = 1;
	else if (key == 0)
		p->pl->left = 1;
	else if (key == 2)
		p->pl->right = 1;
	else if (key == 123)
		p->pl->leftrot = 1;
	else if (key == 124)
		p->pl->rightrot = 1;
	else if (key == 53)
		close_game(p);
	return (0);
}

int		key_release(int key, t_param *p)
{
	if (key == 1)
		p->pl->backward = 0;
	else if (key == 13)
		p->pl->forward = 0;
	else if (key == 0)
		p->pl->left = 0;
	else if (key == 2)
		p->pl->right = 0;
	else if (key == 123)
		p->pl->leftrot = 0;
	else if (key == 124)
		p->pl->rightrot = 0;
	return (0);
}
