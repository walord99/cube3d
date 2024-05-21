/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:41:47 by bplante           #+#    #+#             */
/*   Updated: 2024/05/21 14:42:00 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dbl_vector	get_move_from_input(t_game *game)
{
	t_dbl_vector	movement_dir;

	movement_dir.x = 0;
	movement_dir.y = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		movement_dir = add_vector(movement_dir, game->look_dir);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		movement_dir = add_vector(movement_dir, multiply_vector(game->look_dir,
					-1));
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		movement_dir = add_vector(movement_dir, rotate_vector(game->look_dir,
					deg_to_rad(-90)));
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		movement_dir = add_vector(movement_dir, rotate_vector(game->look_dir,
					deg_to_rad(90)));
	return (movement_dir);
}

void	rotate_player_from_input(t_game *game)
{
	double	rot_speed;

	rot_speed = game->mlx->delta_time * 90;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_player(game, rot_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_player(game, -rot_speed);
	if (!mlx_is_key_down(game->mlx, MLX_KEY_LEFT_ALT))
	{
		mlx_get_mouse_pos(game->mlx, &game->mouse_pos.x, &game->mouse_pos.y);
		game->mouse_pos.x = game->mouse_pos.x - SCREENWIDTH / 2;
		game->mouse_pos.y = game->mouse_pos.y - SCREENHEIGHT / 2;
		mlx_set_mouse_pos(game->mlx, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	}
	rotate_player(game, game->mouse_pos.x / 20);
}
