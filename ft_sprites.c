/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:35:26 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/21 15:46:22 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	sort_sprites(t_mlx *mlx, t_player *pl)
{
	double		distance[mlx->spr_number];
	int			tmp;
	int			disttmp;
	int			i;

	i = -1;
	while (++i < mlx->spr_number)
	{
		distance[i] = ((pl->pos_x - mlx->sprites[i].x) * (pl->pos_x -
		mlx->sprites[i].x) + (pl->pos_y - mlx->sprites[i].y) * (pl->pos_y -
		mlx->sprites[i].y));
		mlx->spr_order[i] = i;
	}
	i = -1;
	while (++i < mlx->spr_number - 1)
		if (distance[i] < distance[i + 1])
		{
			disttmp = distance[i];
			distance[i] = distance[i + 1];
			distance[i + 1] = disttmp;
			tmp = mlx->spr_order[i];
			mlx->spr_order[i] = mlx->spr_order[i + 1];
			mlx->spr_order[i + 1] = tmp;
			i = -1;
		}
}

void	sprite_height(t_sprtools *sprite, t_mlx *mlx)
{
	sprite->spriteheight = abs((int)(mlx->screen_h / (sprite->transformy)));
	sprite->drawstarty = -sprite->spriteheight / 2 + mlx->screen_h / 2;
	if (sprite->drawstarty < 0)
		sprite->drawstarty = 0;
	sprite->drawendy = sprite->spriteheight / 2 + mlx->screen_h / 2;
	if (sprite->drawendy >= mlx->screen_h)
		sprite->drawendy = mlx->screen_h;
}

void	sprite_width(t_sprtools *sprite, t_mlx *mlx)
{
	sprite->spritewidth = abs((int)(mlx->screen_h / (sprite->transformy)));
	sprite->drawstartx = -sprite->spritewidth / 2 + sprite->spritescreenx;
	if (sprite->drawstartx < 0)
		sprite->drawstartx = 0;
	sprite->drawendx = sprite->spritewidth / 2 + sprite->spritescreenx;
	if (sprite->drawendx >= mlx->screen_w)
		sprite->drawendx = mlx->screen_w;
}

void	drawspritelines(t_sprtools *sprite, t_mlx *mlx, t_ray *ray)
{
	sprite->x = sprite->drawstartx;
	while (sprite->x < sprite->drawendx)
	{
		sprite->tex_x = (int)((sprite->x - (-sprite->spritewidth / 2 +
		sprite->spritescreenx)) * mlx->txt->text5_w / sprite->spritewidth);
		sprite->y = sprite->drawstarty;
		if (sprite->transformy > 0 && sprite->x >= 0 &&
		sprite->x < mlx->screen_w &&
		sprite->transformy < (float)ray->zbuffer[sprite->x])
			while (sprite->y < sprite->drawendy)
			{
				sprite->d = (sprite->y) * 256 - mlx->screen_h * 128 +
				sprite->spriteheight * 128;
				sprite->tex_y = ((sprite->d * mlx->txt->text5_h) /
				sprite->spriteheight) / 256;
				if (*(mlx->txt->txt5_data + sprite->tex_x + sprite->tex_y *
				mlx->txt->text5_sl / 4))
					*(mlx->d_ad + sprite->x + sprite->y *
					mlx->sl / 4) = *(mlx->txt->txt5_data +
					sprite->tex_x + sprite->tex_y * mlx->txt->text5_sl / 4);
				sprite->y++;
			}
		sprite->x++;
	}
}

void	drawsprites(t_mlx *mlx, t_player *pl, t_world *map, t_ray *ray)
{
	int			i;
	t_spriteptr	sprite_ptr;
	t_sprtools	sprite;

	sort_sprites(mlx, pl);
	i = 0;
	while (i < mlx->spr_number)
	{
		sprite_ptr = mlx->sprites[mlx->spr_order[i++]];
		sprite.spritex = (sprite_ptr.x + 0.5) - pl->pos_x;
		sprite.spritey = (sprite_ptr.y + 0.5) - pl->pos_y;
		sprite.invdet = 1.0 / (pl->plane_x *
		pl->dir_y - pl->dir_x * pl->plane_y);
		sprite.transformx = sprite.invdet * (pl->dir_y *
		sprite.spritex - pl->dir_x * sprite.spritey);
		sprite.transformy = sprite.invdet *
		(-pl->plane_y * sprite.spritex + pl->plane_x * sprite.spritey);
		sprite.spritescreenx = (int)((mlx->screen_w / 2) *
		(1 + sprite.transformx / sprite.transformy));
		sprite_height(&sprite, mlx);
		sprite_width(&sprite, mlx);
		drawspritelines(&sprite, mlx, ray);
	}
}
