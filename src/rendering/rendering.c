/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:13:31 by bplante           #+#    #+#             */
/*   Updated: 2024/04/30 02:43:31 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	rbga_builder(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw(t_game *game)
{
	t_raycaster	ray_info;
	t_draw_info	di;

	di.screen_pos.x = 0;
	while (di.screen_pos.x < screenWidth)
	{
		di.cameraX = 2 * di.screen_pos.x / (double)screenWidth - 1;
		ray_info.rayDir = add_vector(game->look_dir, multiply_vector(game->plane,
					di.cameraX));
		cast_ray(&ray_info, game);
		di.lineHeight = screenHeight / ray_info.perpWallDist;
		di.drawStart = -di.lineHeight / 2 + screenHeight / 2;
		if (di.drawStart < 0)
			di.drawStart = 0;
		di.drawEnd = di.lineHeight / 2 + screenHeight / 2;
		if (di.drawEnd >= screenHeight)
			di.drawEnd = screenHeight - 1;
		di.screen_pos.y = di.drawStart;
		di.texX = (int)(ray_info.wallX * 255);
		if (ray_info.side == 0 && ray_info.rayDir.x > 0)
			di.texX = 255 - di.texX - 1;
		if (ray_info.side == 1 && ray_info.rayDir.y < 0)
			di.texX = 255 - di.texX - 1;
		while (di.screen_pos.y <= di.drawEnd)
		{
			mlx_put_pixel(game->rendered,di. screen_pos.x, di.screen_pos.y,
				rbga_builder(255, abs(di.texX - 255), di.texX, 255));
			di.screen_pos.y++;
		}
		di.screen_pos.x++;
	}
}
