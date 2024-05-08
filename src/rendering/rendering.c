/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:13:31 by bplante           #+#    #+#             */
/*   Updated: 2024/05/07 23:43:12 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_pixel_color(int x, int y, int cx, int cy, t_game *game)
{
	t_dbl_vector	relpos;
	t_dbl_vector	pos;
	t_dbl_vector	*rot_pre = game->minimap.norm_rot;

	relpos.x = (x - cx) * 0.05;
	relpos.y = (y - cy) * 0.05;
	pos = add_vector(add_vector(multiply_vector(rot_pre[0], relpos.x), multiply_vector(rot_pre[1], relpos.y)), game->pos);
	if (get_map_coordinate((int)pos.x, (int)pos.y, &game->map))
		mlx_put_pixel(game->minimap.render, x, y, rbga_builder(255, 255, 255, 255));
	else
		mlx_put_pixel(game->minimap.render, x, y, rbga_builder(0, 0, 0, 255));
}

void	itterate_fill(int x, int y, int cx, int cy, t_game *game)
{
	int	dir;

	dir = -1;
	if (x < cx)
		dir = 1;
	while (x != cx)
	{
		get_pixel_color(x, y, cx, cy, game);
		x += dir;
	}
	if (dir == 1)
		get_pixel_color(x, y, cx, cy, game);
}

void	midPointCircleFill(int center_x, int center_y, int r, t_game *game)
{
	int	r2;
	int	x;
	int	y;
	int	dy;
	int	dx;
	int	d;

	r2 = r + r;
	x = r;
	y = 0;
	dy = -2;
	dx = r2 + r2 - 4;
	d = r2 - 1;
	while (y <= x)
	{
		itterate_fill(center_x - x, center_y - y, center_x, center_y, game);
		itterate_fill(center_x + x, center_y - y, center_x, center_y, game);
		itterate_fill(center_x - x, center_y + y, center_x, center_y, game);
		itterate_fill(center_x + x, center_y + y, center_x, center_y, game);
		itterate_fill(center_x - y, center_y - x, center_x, center_y, game);
		itterate_fill(center_x + y, center_y - x, center_x, center_y, game);
		itterate_fill(center_x - y, center_y + x, center_x, center_y, game);
		itterate_fill(center_x + y, center_y + x, center_x, center_y, game);
		d += dy;
		dy -= 4;
		y++;
		if (d < 0)
		{
			d += dx;
			dx -= 4;
			x--;
		}
	}
}

void	draw_minimap(t_game *game)
{
	mlx_delete_image(game->mlx, game->minimap.render);
	game->minimap.norm_rot[0] = rotate_vector(game->look_dir, deg_to_rad(90));
	game->minimap.norm_rot[1] = rotate_vector(game->look_dir, deg_to_rad(180));
	game->minimap.render = mlx_new_image(game->mlx, screenHeight / 4 + 5, screenHeight / 4 + 5);
	midPointCircleFill(screenHeight / 4 / 2, screenHeight / 4 / 2, screenHeight / 4 / 2, game);
	mlx_image_to_window(game->mlx, game->minimap.render, screenWidth - screenHeight / 4, 0);
	game->minimap.render->instances[0].z = 2;
}

uint32_t	rbga_builder(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw(t_game *game)
{
	t_raycaster	ray_info;
	t_draw_info	di;

	di.screen_pos.x = 0;
	ray_info.start_pos = game->pos;
	while (di.screen_pos.x < screenWidth)
	{
		di.cameraX = 2 * di.screen_pos.x / (double)screenWidth - 1;
		ray_info.rayDir = add_vector(game->look_dir,
				multiply_vector(game->plane, di.cameraX));
		cast_ray(&ray_info, &game->map);
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
			mlx_put_pixel(game->rendered, di.screen_pos.x, di.screen_pos.y,
				rbga_builder(255, abs(di.texX - 255), di.texX, 255));
			di.screen_pos.y++;
		}
		di.screen_pos.x++;
	}
}
