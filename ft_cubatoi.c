/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cubatoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:00:46 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/20 13:24:26 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static int	numlen(const char *str)
{
	int i;

	i = 0;
	while (ft_isdigit(*str))
	{
		i++;
		str++;
	}
	return (i);
}

int			ft_cubatoi_r(const char *str)
{
	long int	n;

	n = 0;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (numlen(str) > 4)
		return (42000);
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			break ;
	}
	return ((int)(n));
}

int			ft_cubatoi_f(const char *str)
{
	long int	n;

	n = 0;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (numlen(str) > 3)
		return (-1);
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			break ;
	}
	if (n < 0 || n > 255)
		return (-1);
	return ((int)(n));
}
