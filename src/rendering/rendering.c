/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:13:31 by bplante           #+#    #+#             */
/*   Updated: 2024/05/23 11:38:30 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	set_draw_info(t_draw_info *di, t_raycaster *ray_info)
{
	di->line_height = SCREENHEIGHT / ray_info->perp_wall_dist;
	di->draw_start = -di->line_height / 2 + SCREENHEIGHT / 2;
	if (di->draw_start < 0)
		di->draw_start = 0;
	di->draw_end = di->line_height / 2 + SCREENHEIGHT / 2;
	if (di->draw_end >= SCREENHEIGHT)
		di->draw_end = SCREENHEIGHT - 1;
	di->screen_pos.y = di->draw_start;
	di->tex_x = (int)(ray_info->wall_x * (double)di->texture->width);
	if (ray_info->side == 0 && ray_info->ray_dir.x > 0)
		di->tex_x = di->texture->width - di->tex_x - 1;
	if (ray_info->side == 1 && ray_info->ray_dir.y < 0)
		di->tex_x = di->texture->width - di->tex_x - 1;
	di->step = 1.0 * di->texture->height / di->line_height;
	di->tex_pos = (di->draw_start - SCREENHEIGHT / 2 + di->line_height / 2)
		* di->step;
}

void	render_wall(t_game *game)
{
	t_raycaster	ray_info;
	t_draw_info	di;

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
		set_draw_info(&di, &ray_info);
		while (di.screen_pos.y <= di.draw_end)
		{
			di.tex_y = (int)di.tex_pos;
			di.tex_pos += di.step;
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
