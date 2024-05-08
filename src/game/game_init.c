/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:23:23 by bplante           #+#    #+#             */
/*   Updated: 2024/05/08 17:10:19 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void fill_square(mlx_image_t *img, uint32_t color, t_int_vector start, t_int_vector end)
{
	int temp = start.y;
	while(start.x != end.x)
	{
		start.y = temp;
		while(start.y != end.y)
		{
			mlx_put_pixel(img, start.x, start.y, color);
			start.y++;
		}
		start.x++;
	}
}

mlx_image_t *create_floor_ceil_image(t_game *game)
{
	mlx_image_t *fc_img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	t_int_vector start;
	t_int_vector end;
	start.x = 0;
	start.y = 0;
	end.x = SCREENWIDTH;
	end.y = SCREENHEIGHT / 2;
	fill_square(fc_img, game->map.cieling, start, end);
	start.y = SCREENHEIGHT / 2;
	start.x = 0;
	end.x = SCREENWIDTH;
	end.y = SCREENHEIGHT;
	fill_square(fc_img, game->map.floor, start, end);
	return fc_img;
}

void init_player_move_box(t_game *game)
{
	game->AABB_corners[0].x = -PLAYER_MOVE_BOX;
	game->AABB_corners[0].y = -PLAYER_MOVE_BOX;
	game->AABB_corners[1].x = PLAYER_MOVE_BOX;
	game->AABB_corners[1].y = -PLAYER_MOVE_BOX;
	game->AABB_corners[2].x = PLAYER_MOVE_BOX;
	game->AABB_corners[2].y = PLAYER_MOVE_BOX;
	game->AABB_corners[3].x = -PLAYER_MOVE_BOX;
	game->AABB_corners[3].y = PLAYER_MOVE_BOX;
}

void	init_game(t_game *game)
{
	// t_dbl_vector mov;
	// mov.x = 0;
	// mov.y = 0;
	game->pos.x = game->map.spawn_x + 0.5;
	game->pos.y = game->map.spawn_y + 0.5;
	game->look_dir.x = 0;
	game->look_dir.y = -1;
	game->plane.x = 1;
	game->plane.y = 0;
	game->rendered = NULL;
	game->minimap.render = NULL;
	init_player_move_box(game);
	// game->look_dir = rotate_vector(game->look_dir, deg_to_rad(2));
	// game->plane = rotate_vector(game->plane, deg_to_rad(2));
	// mlx_set_setting(MLX_FULLSCREEN, true);
	// mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "cub3d", false);
	//game->minimap->instances[0].z = 3;
	game->fc_img = create_floor_ceil_image(game);
	mlx_image_to_window(game->mlx, game->fc_img, 0, 0);
	game->fc_img->instances[0].z = 0;
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	// collision_detection(game, );
	mlx_loop_hook(game->mlx, &loop_hook, game);
	mlx_loop(game->mlx);
}