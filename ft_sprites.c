/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:35:26 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/17 17:48:17 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	sort_sprites(t_mlx *mlx, t_player *pl)
{
	double		distance[mlx->spr_number];
	int 		tmp;
	int			disttmp;
	int 		i;

	i = -1;
	while (++i < mlx->spr_number)
	{
		distance[i] = ((pl->pos_x - mlx->sprites[i]->x) * (pl->pos_x - mlx->sprites[i]->x) + (pl->pos_y - mlx->sprites[i]->y) * (pl->pos_y - mlx->sprites[i]->y));
		mlx->spr_order[i] = i;
	}
	i = -1;
	while(++i < mlx->spr_number - 1)
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

void	drawsprites(t_mlx *mlx, t_player *pl, t_world *map, t_ray *ray)
{
	int i;
	t_sprite sprite;

	sort_sprites(mlx, pl);
	i = 0;
	while (i < mlx->spr_number)
	{
		sprite = *(mlx->sprites[mlx->spr_order[i]]);
		i++;

		float sprite_x = sprite.x + 0.5;
		float sprite_y = sprite.y + 0.5;
		//translate sprite position to relative to camera
		double spriteX = sprite_x - pl->pos_x;
		double spriteY = sprite_y - pl->pos_y;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (pl->plane_x * pl->dir_y - pl->dir_x * pl->plane_y); //required for correct matrix multiplication
		double transformX = invDet * (pl->dir_y * spriteX - pl->dir_x * spriteY);
		double transformY = invDet * (-pl->plane_y * spriteX + pl->plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D
		int spriteScreenX = (int)((mlx->screen_w / 2) * (1 + transformX / transformY));

		// SPRITE LINE
		int spriteHeight = abs((int)(mlx->screen_h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		int drawStartY = -spriteHeight / 2 + mlx->screen_h / 2;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + mlx->screen_h / 2;
		if(drawEndY >= mlx->screen_h) drawEndY = mlx->screen_h;

		// SPRITE WIDTH
		int spriteWidth = abs((int)(mlx->screen_h / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= mlx->screen_w)
			drawEndX = mlx->screen_w;

		// DRAWING SPRITE
		int x = drawStartX;
		int y;

		while (x < drawEndX)
		{
			int texX = (int)((x - (-spriteWidth / 2 + spriteScreenX)) * mlx->txt->text5_w / spriteWidth);
			y = drawStartY;
			if(transformY > 0 && x >= 0 && x < mlx->screen_w && transformY < (float)ray->Zbuffer[x])
				while(y < drawEndY)
				{
					int d = (y) * 256 - mlx->screen_h * 128 + spriteHeight * 128;
					int texY = ((d * mlx->txt->text5_h) / spriteHeight) / 256;
					
					if(*(mlx->txt->txt5_data + texX + texY * mlx->txt->text5_sl / 4))
						*(mlx->d_ad + x + y * mlx->sl / 4) = *(mlx->txt->txt5_data + texX +
						texY * mlx->txt->text5_sl / 4);
					y++;
				}
			x++;
		}
	}
}