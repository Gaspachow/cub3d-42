/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:09:20 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/19 15:11:12 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	put_error(char *message, t_param *p)
{
	write(2, message, ft_strlen(message));
	// FREE ALL MEMORIES HERE
	exit(EXIT_FAILURE);
}