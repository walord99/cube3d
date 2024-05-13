/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:13:31 by bplante           #+#    #+#             */
/*   Updated: 2024/05/13 13:52:37 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_pixel_color(int x, int y, int cx, int cy, t_game *game)
{
	t_dbl_vector	relpos;
	t_dbl_vector	pos;
	t_dbl_vector	*rot_pre;

	rot_pre = game->minimap.norm_rot;
	relpos.x = (x - cx) * 0.05;
	relpos.y = (y - cy) * 0.05;
	pos = add_vector(add_vector(multiply_vector(rot_pre[0], relpos.x),
				multiply_vector(rot_pre[1], relpos.y)), game->pos);
	if (get_map_coordinate((int)pos.x, (int)pos.y, &game->map) == '1')
		mlx_put_pixel(game->minimap.render, x, y, rbga_builder(255, 255, 255,
				255));
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
	game->minimap.render = mlx_new_image(game->mlx, SCREENHEIGHT / 4 + 5,
			SCREENHEIGHT / 4 + 5);
	midPointCircleFill(SCREENHEIGHT / 4 / 2, SCREENHEIGHT / 4 / 2, SCREENHEIGHT
		/ 4 / 2, game);
	mlx_image_to_window(game->mlx, game->minimap.render, SCREENWIDTH
		- SCREENHEIGHT / 4, 0);
	game->minimap.render->instances[0].z = 2;
}

uint32_t	rbga_builder(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	get_texture_color(int x, int y, mlx_texture_t *tex)
{
	uint8_t *byte;
	if (y >= tex->height)
		y = tex->height - 1;
	if (x >= tex->width)
		x = tex->width -1;
	byte = &tex->pixels[(y * tex->width + (x * -1 + tex->width)) * tex->bytes_per_pixel];
	return (rbga_builder(byte[0], byte[1], byte[2], byte[3]));
}

mlx_texture_t *get_texture(t_game *game, t_raycaster *ri)
{
	if (ri->side == 0)
	{
		if (ri->rayDir.x > 0)
			return game->map.textures[WE];
		return game->map.textures[EA];
	}
	else if (ri->rayDir.y > 0)
		return game->map.textures[SO];
	return game->map.textures[NO];
}

void	draw(t_game *game)
{
	t_raycaster	ray_info;
	t_draw_info	di;
	double		step;
	double		texPos;

	di.screen_pos.x = 0;
	ray_info.start_pos = game->pos;
	while (di.screen_pos.x < SCREENWIDTH)
	{
		di.cameraX = 2 * di.screen_pos.x / (double)SCREENWIDTH - 1;
		ray_info.do_doors = true;
		ray_info.rayDir = add_vector(game->look_dir,
				multiply_vector(game->plane, di.cameraX));
		cast_ray(&ray_info, game);
		di.tex = get_texture(game, &ray_info);
		di.lineHeight = SCREENHEIGHT / ray_info.perpWallDist;
		di.drawStart = -di.lineHeight / 2 + SCREENHEIGHT / 2;
		if (di.drawStart < 0)
			di.drawStart = 0;
		di.drawEnd = di.lineHeight / 2 + SCREENHEIGHT / 2;
		if (di.drawEnd >= SCREENHEIGHT)
			di.drawEnd = SCREENHEIGHT - 1;
		di.screen_pos.y = di.drawStart;
		di.texX = (int)(ray_info.wallX * (double)di.tex->width);
		if (ray_info.side == 0 && ray_info.rayDir.x > 0)
			di.texX = di.tex->width - di.texX - 1;
		if (ray_info.side == 1 && ray_info.rayDir.y < 0)
			di.texX = di.tex->width - di.texX - 1;
		step = 1.0 * di.tex->height / di.lineHeight;
		texPos = (di.drawStart - SCREENHEIGHT / 2 + di.lineHeight / 2) * step;
		while (di.screen_pos.y <= di.drawEnd)
		{
			di.texY = (int)texPos;// & (game->map.textures[1]->height - 1);
			texPos += step;
			mlx_put_pixel(game->rendered, di.screen_pos.x, di.screen_pos.y,
				get_texture_color(di.texX, di.texY, game->map.textures[1]));
			di.screen_pos.y++;
		}
		di.screen_pos.x++;
	}
}
