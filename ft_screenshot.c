/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screenshot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:04:08 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/21 14:42:22 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	int_to_char(unsigned char *c, int i)
{
	c[0] = (unsigned char)(i);
	c[1] = (unsigned char)(i >> 8);
	c[2] = (unsigned char)(i >> 16);
	c[3] = (unsigned char)(i >> 24);
}

int		bmp_header(int fd, int h, int w, int padsize)
{
	unsigned char	header[54];
	int				filesize;

	filesize = 54 + (w * 3 * h) + (padsize * h);
	ft_bzero(header, 54);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	int_to_char(header + 2, filesize);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	int_to_char(header + 18, w);
	int_to_char(header + 22, h);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	return (!(write(fd, header, 54) < 0));
}

int		bmp_data(int fd, t_mlx *mlx, int padsize)
{
	unsigned char	zero[3];
	int				x;
	int				y;
	int				pixel;

	y = mlx->screen_h - 1;
	ft_bzero(zero, 3);
	while (y >= 0)
	{
		x = 0;
		while (x < mlx->screen_w)
		{
			pixel = *(mlx->d_ad + x + y * mlx->sl / 4);
			if (write(fd, &pixel, 3) < 0)
				return (0);
			if (padsize > 0 && write(fd, &zero, padsize) < 0)
				return (0);
			x++;
		}
		y--;
	}
	return (1);
}

int		take_screenshot(t_param *p)
{
	int padsize;
	int fd;

	run_game(p);
	padsize = (4 - ((int)p->mlx->screen_w * 3) % 4) % 4;
	if ((fd = open("screenshot.bmp", O_WRONLY |
	O_CREAT, 0777 | O_TRUNC | O_APPEND)) < 0)
		return (0);
	bmp_header(fd, p->mlx->screen_h, p->mlx->screen_w, padsize);
	bmp_data(fd, p->mlx, padsize);
	close(fd);
	return (1);
}

void	make_screenshot(t_param *p, char *str)
{
	if (ft_strncmp("--save", str, 7) != 0)
		put_error("ERROR\nUnrecognized second argument\n", p);
	p->screenshot = 1;
	write(1, "Saving screenshot...\n", 21);
	if (!take_screenshot(p))
		put_error("ERROR\nCouldn't create/open screenshot.bmp\n", p);
	write(1, "Screenshot saved!\n", 18);
	close_game(p);
}
