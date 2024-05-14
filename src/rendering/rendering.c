/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:13:31 by bplante           #+#    #+#             */
/*   Updated: 2024/05/14 17:04:44 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_pixel_color(t_int_vector pixel_pos, t_int_vector center,
		t_game *game)
{
	t_dbl_vector	relpos;
	t_dbl_vector	pos;
	t_dbl_vector	*rot_pre;
	char			tile;

	rot_pre = game->minimap.norm_rot;
	relpos.x = (pixel_pos.x - center.x) * 0.05;
	relpos.y = (pixel_pos.y - center.y) * 0.05;
	pos = add_vector(add_vector(multiply_vector(rot_pre[0], relpos.x),
				multiply_vector(rot_pre[1], relpos.y)), game->pos);
	tile = get_map_loc((int)pos.x, (int)pos.y, &game->map);
	if (tile == '1')
		mlx_put_pixel(game->minimap.render, pixel_pos.x, pixel_pos.y,
			rbga_builder(0, 0, 0, 255));
	else if (tile == '-' || tile == '|')
		mlx_put_pixel(game->minimap.render, pixel_pos.x, pixel_pos.y,
			rbga_builder(0, 0, 0, 150));
}

void	itterate_fill(t_int_vector pos, t_int_vector center, t_game *game)
{
	int	dir;

	dir = -1;
	if (pos.x < center.x)
		dir = 1;
	while (pos.x != center.x)
	{
		get_pixel_color(pos, center, game);
		pos.x += dir;
	}
	if (dir == 1)
		get_pixel_color(pos, center, game);
}

void	mid_point_circle_fill(int center_x, int center_y, int r, t_game *game)
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
		itterate_fill((t_int_vector){.x = center_x - x, .y = center_y - y},
			(t_int_vector){.x = center_x, .y = center_y}, game);
		itterate_fill((t_int_vector){.x = center_x + x, .y = center_y - y},
			(t_int_vector){.x = center_x, .y = center_y}, game);
		itterate_fill((t_int_vector){.x = center_x - x, .y = center_y + y},
			(t_int_vector){.x = center_x, .y = center_y}, game);
		itterate_fill((t_int_vector){.x = center_x + x, .y = center_y + y},
			(t_int_vector){.x = center_x, .y = center_y}, game);
		itterate_fill((t_int_vector){.x = center_x - y, .y = center_y - x},
			(t_int_vector){.x = center_x, .y = center_y}, game);
		itterate_fill((t_int_vector){.x = center_x + y, .y = center_y - x},
			(t_int_vector){.x = center_x, .y = center_y}, game);
		itterate_fill((t_int_vector){.x = center_x - y, .y = center_y + x},
			(t_int_vector){.x = center_x, .y = center_y}, game);
		itterate_fill((t_int_vector){.x = center_x + y, .y = center_y + x},
			(t_int_vector){.x = center_x, .y = center_y}, game);
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

void	render_minimap(t_game *game)
{
	mlx_delete_image(game->mlx, game->minimap.render);
	game->minimap.norm_rot[0] = rotate_vector(game->look_dir, deg_to_rad(90));
	game->minimap.norm_rot[1] = rotate_vector(game->look_dir, deg_to_rad(180));
	game->minimap.render = mlx_new_image(game->mlx, SCREENHEIGHT / 4 + 5,
			SCREENHEIGHT / 4 + 5);
	mid_point_circle_fill(SCREENHEIGHT / 4 / 2, SCREENHEIGHT / 4 / 2,
		SCREENHEIGHT / 4 / 2, game);
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
	uint8_t	*byte;

	if (y >= tex->height - 1)
		y = tex->height - 2;
	if (x >= tex->width - 1)
		x = tex->width - 2;
	byte = &tex->pixels[(y * tex->width + (x * -1 + tex->width))
		* tex->bytes_per_pixel];
	return (rbga_builder(byte[0], byte[1], byte[2], byte[3]));
}

mlx_texture_t	*get_texture(t_game *game, t_raycaster *ri)
{
	char	tile;

	tile = get_map_loc(ri->map_pos.x, ri->map_pos.y, &game->map);
	if (tile == '-' || tile == '|')
	{
		return (game->map.textures[DOOR]);
	}
	if (ri->side == 0)
	{
		if (ri->ray_dir.x > 0)
			return (game->map.textures[EA]);
		return (game->map.textures[WE]);
	}
	else if (ri->ray_dir.y > 0)
		return (game->map.textures[SO]);
	return (game->map.textures[NO]);
}

void	render_wall(t_game *game)
{
	t_raycaster	ray_info;
	t_draw_info	di;
	double		step;
	double		tex_pos;

	di.screen_pos.x = 0;
	ray_info.start_pos = game->pos;
	while (di.screen_pos.x < SCREENWIDTH)
	{
		di.camera_x = 2 * di.screen_pos.x / (double)SCREENWIDTH - 1;
		ray_info.do_doors = true;
		ray_info.ray_dir = add_vector(game->look_dir,
				multiply_vector(game->plane, di.camera_x));
		cast_ray(&ray_info, game);
		di.texture = get_texture(game, &ray_info);
		di.line_height = SCREENHEIGHT / ray_info.perp_wall_dist;
		di.draw_start = -di.line_height / 2 + SCREENHEIGHT / 2;
		if (di.draw_start < 0)
			di.draw_start = 0;
		di.draw_end = di.line_height / 2 + SCREENHEIGHT / 2;
		if (di.draw_end >= SCREENHEIGHT)
			di.draw_end = SCREENHEIGHT - 1;
		di.screen_pos.y = di.draw_start;
		di.tex_x = (int)(ray_info.wall_x * (double)di.texture->width);
		if (ray_info.side == 0 && ray_info.ray_dir.x > 0)
			di.tex_x = di.texture->width - di.tex_x - 1;
		if (ray_info.side == 1 && ray_info.ray_dir.y < 0)
			di.tex_x = di.texture->width - di.tex_x - 1;
		step = 1.0 * di.texture->height / di.line_height;
		tex_pos = (di.draw_start - SCREENHEIGHT / 2 + di.line_height / 2)
			* step;
		while (di.screen_pos.y <= di.draw_end)
		{
			di.tex_y = (int)tex_pos; // & (game->map.textures[1]->height - 1);
			tex_pos += step;
			mlx_put_pixel(game->rendered, di.screen_pos.x, di.screen_pos.y,
				get_texture_color(di.tex_x, di.tex_y, di.texture));
			di.screen_pos.y++;
		}
		di.screen_pos.x++;
	}
}

void	draw(t_game *game)
{
	mlx_delete_image(game->mlx, game->rendered);
	game->rendered = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	render_wall(game);
	mlx_image_to_window(game->mlx, game->rendered, 0, 0);
	game->rendered->instances[0].z = 1;
	render_minimap(game);
}
