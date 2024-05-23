/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:20:44 by bplante           #+#    #+#             */
/*   Updated: 2024/05/23 00:54:04 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door	*get_door(int x, int y, t_game *game)
{
	int	i;

	i = 0;
	while (game->doors[i] != NULL)
	{
		if (game->doors[i]->map_pos.x == x && game->doors[i]->map_pos.y == y)
			return (game->doors[i]);
		i++;
	}
	return (NULL);
}

void	door_handler(t_game *game)
{
	t_dbl_vector	relpos;
	double			mag_sqrd;
	int				i;

	i = 0;
	while (game->doors[i])
	{
		relpos.x = game->doors[i]->map_pos.x + 0.5 - game->pos.x;
		relpos.y = game->doors[i]->map_pos.y + 0.5 - game->pos.y;
		mag_sqrd = pow(relpos.x, 2) + pow(relpos.y, 2);
		if (mag_sqrd < pow(1.8, 2))
		{
			game->doors[i]->open_track += 0.6 * game->mlx->delta_time;
			if (game->doors[i]->open_track > 1)
				game->doors[i]->open_track = 1;
		}
		else
		{
			game->doors[i]->open_track -= 0.6 * game->mlx->delta_time;
			if (game->doors[i]->open_track < 0)
				game->doors[i]->open_track = 0;
		}
		i++;
	}
}

void	rotate_player(t_game *game, double rot)
{
	double	rad;

	rad = deg_to_rad(rot);
	game->look_dir = rotate_vector(game->look_dir, rad);
	game->plane = rotate_vector(game->plane, rad);
}

void	loop_hook(void *param)
{
	t_game			*game;
	t_dbl_vector	movement_dir;
	double			move_speed;
	t_dbl_vector	movement;

	game = (t_game *)param;
	move_speed = game->mlx->delta_time * 3.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	movement_dir = get_move_from_input(game);
	movement_dir = round_off_floating_point_errors(movement_dir);
	movement_dir = normalise_vector(movement_dir);
	movement = multiply_vector(movement_dir, move_speed);
	game->pos = collision_detection(game, movement, movement_dir);
	door_handler(game);
	rotate_player_from_input(game);
	draw(game);
}
