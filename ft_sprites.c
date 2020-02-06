/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:35:26 by gsmets            #+#    #+#             */
/*   Updated: 2020/02/06 15:07:28 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	drawsprites(t_mlx *mlx, t_player *pl, t_world *map, t_ray *ray)
{
	int sprite_x = 10;
	int sprite_y = 10;
	//translate sprite position to relative to camera
	double spriteX = sprite_x - map->x;
	double spriteY = sprite_y - map->y;

	//transform sprite with the inverse camera matrix
	// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
	// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
	// [ planeY   dirY ]                                          [ -planeY  planeX ]

	double invDet = 1.0 / (pl->plane_x * pl->dir_y - pl->dir_x * pl->plane_y); //required for correct matrix multiplication

	double transformX = invDet * (pl->dir_y * spriteX - pl->dir_x * spriteY);
	double transformY = invDet * (-pl->plane_y * spriteX + pl->plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

	int spriteScreenX = (int)((mlx->screen_w / 2) * (1 + transformX / transformY));

	//calculate height of the sprite on screen
	int spriteHeight = abs((int)(mlx->screen_h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
	//calculate lowest and highest pixel to fill in current stripe
	int drawStartY = -spriteHeight / 2 + mlx->screen_h / 2;
	if(drawStartY < 0) drawStartY = 0;
	int drawEndY = spriteHeight / 2 + mlx->screen_h / 2;
	if(drawEndY >= mlx->screen_h) drawEndY = mlx->screen_h - 1;

	//calculate width of the sprite
	int spriteWidth = abs( (int)(mlx->screen_h / (transformY)));
	int drawStartX = -spriteWidth / 2 + spriteScreenX;
	if(drawStartX < 0)
		drawStartX = 0;
	int drawEndX = spriteWidth / 2 + spriteScreenX;
	if(drawEndX >= mlx->screen_w)
		drawEndX = mlx->screen_w - 1;

	//loop through every vertical stripe of the sprite on screen
	for(int stripe = drawStartX; stripe < drawEndX; stripe++)
	{
	int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * mlx->txt->text5_w / spriteWidth) / 256;
	//the conditions in the if are:
	//1) it's in front of camera plane so you don't see things behind you
	//2) it's on the screen (left)
	//3) it's on the screen (right)
	//4) ZBuffer, with perpendicular distance
	if(transformY > 0 && stripe > 0 && stripe < mlx->screen_w /*&& transformY < ZBuffer[stripe]*/)
	for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
	{
		int d = (y) * 256 - mlx->screen_h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
		int texY = ((d * mlx->txt->text5_h) / spriteHeight) / 256;
		
		*(mlx->d_ad + stripe + y * mlx->sl / 4) = *(mlx->txt->txt5_data + texX +
		texY * mlx->text_sl / 4);
		// Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
		// if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
	}
	}
}