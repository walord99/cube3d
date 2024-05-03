/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:23:23 by bplante           #+#    #+#             */
/*   Updated: 2024/05/03 19:11:45 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	init_player_move_box(game);
	// game->look_dir = rotate_vector(game->look_dir, deg_to_rad(2));
	// game->plane = rotate_vector(game->plane, deg_to_rad(2));
	// mlx_set_setting(MLX_FULLSCREEN, true);
	// mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init(screenWidth, screenHeight, "cub3d", false);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	// collision_detection(game, );
	mlx_cursor_hook(game->mlx, &mouse_hook, game);
	mlx_loop_hook(game->mlx, &loop_hook, game);
	mlx_loop(game->mlx);
}