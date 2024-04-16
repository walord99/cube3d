/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:13:31 by bplante           #+#    #+#             */
/*   Updated: 2024/04/16 09:57:46 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	rbga_builder(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	cast_rays(t_game *game)
{
	double		cameraX;
	int			mapX;
	int			mapY;
	t_vector	rayDir;
	t_vector	sideDist;
	t_vector	deltaDist;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			x;
	int			y;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;

	x = 0;
	while (x < screenWidth)
	{
		cameraX = 2 * x / (double)screenWidth - 1;
		rayDir = add_vector(game->look_dir, multiply_vector(game->plane,
					cameraX));
		mapX = game->pos.x / 1;
		mapY = game->pos.y / 1;
		if (rayDir.x == 0)
			deltaDist.x = DBL_MAX;
		else
			deltaDist.x = dbl_abs(1 / rayDir.x);
		if (rayDir.y == 0)
			deltaDist.y = DBL_MAX;
		else
			deltaDist.y = dbl_abs(1 / rayDir.y);
		if (rayDir.x < 0)
		{
			stepX = -1;
			sideDist.x = (game->pos.x - mapX) * deltaDist.x;
		}
		else
		{
			stepX = 1;
			sideDist.x = (1 + mapX - game->pos.x) * deltaDist.x;
		}
		if (rayDir.y < 0)
		{
			stepY = -1;
			sideDist.y = (game->pos.y - mapY) * deltaDist.y;
		}
		else
		{
			stepY = 1;
			sideDist.y = (1 + mapY - game->pos.y) * deltaDist.y;
		}
		hit = 0;
		while (hit == 0)
		{
			if (sideDist.x < sideDist.y)
			{
				sideDist.x += deltaDist.x;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDist.y += deltaDist.y;
				;
				mapY += stepY;
				side = 1;
			}
			if (get_map_coordinate(mapX, mapY, game->map) != 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = sideDist.x - deltaDist.x;
		else
			perpWallDist = sideDist.y - deltaDist.y;
		lineHeight = screenHeight / perpWallDist;
		drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		y = drawStart;
		while (y <= drawEnd)
		{
			if (side == 0)
				mlx_put_pixel(game->rendered, x, y, rbga_builder(255, 255, 255,
						255));
			else
				mlx_put_pixel(game->rendered, x, y, rbga_builder(200, 200, 200,
						255));
			y++;
		}
		x++;
	}
}
