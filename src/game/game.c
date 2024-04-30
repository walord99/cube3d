/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:20:44 by bplante           #+#    #+#             */
/*   Updated: 2024/04/30 14:47:58 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook(mlx_key_data_t key_data, void *param)
{
	t_game	*game;

	game = (t_game *)param;
}

int	clamp(int range_start, int range_end, int num)
{
	if (num < range_start)
		return (range_start);
	if (num > range_end)
		return (range_end);
	return (num);
}

t_dbl_vector	collision_detection(t_game *game, t_dbl_vector movement, t_dbl_vector movement_dir)
{
	t_raycaster ray_info;
	t_dbl_vector newpos;
	t_dbl_vector hitloc;

	movement_dir.y = -1;
	movement_dir.x = -1;
	ray_info.rayDir = normalise_vector(movement_dir);
	newpos = add_vector(game->pos, movement);
	hitloc = cast_ray(&ray_info, game, PLAYER_MOVE_BOX);
	

	return (newpos);
}

void	mouse_hook(double xpos, double ypos, void *param)
{
	// printf("x: %f\ny: %f\n", xpos, ypos);
}

void	loop_hook(void *param)
{
	t_game		*game;
	t_dbl_vector	movement_dir;
	double		move_speed;
	double		rot_speed;
	int			mapX;
	int			mapY;
	t_dbl_vector	temp_pos;
	double		x_offset;
	double		y_offset;
	t_dbl_vector	movement;

	game = (t_game *)param;
	movement_dir.x = 0;
	movement_dir.y = 0;
	move_speed = game->mlx->delta_time * 3.0;
	rot_speed = game->mlx->delta_time * 90.0;
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
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->look_dir = rotate_vector(game->look_dir, deg_to_rad(rot_speed));
		game->plane = rotate_vector(game->plane, deg_to_rad(rot_speed));
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->look_dir = rotate_vector(game->look_dir, deg_to_rad(-1
					* rot_speed));
		game->plane = rotate_vector(game->plane, deg_to_rad(-1 * rot_speed));
	}
	movement_dir = round_off_floating_point_errors(movement_dir);
	movement_dir = normalise_vector(movement_dir);
	movement = multiply_vector(movement_dir, move_speed);
	game->pos =  collision_detection(game, movement, movement_dir);
	printf("x:%f\ty:%f\n", game->pos.x, game->pos.y);
	mlx_delete_image(game->mlx, game->rendered);
	game->rendered = mlx_new_image(game->mlx, screenWidth, screenWidth);
	draw(game);
	mlx_image_to_window(game->mlx, game->rendered, 0, 0);
}

void	init_game(t_game *game)
{
	// t_dbl_vector mov;
	// mov.x = 0;
	// mov.y = 0;
	game->pos.x = 2;
	game->pos.y = 3.1;
	game->look_dir.x = 1;
	game->look_dir.y = 1;
	game->plane.x = 1;
	game->plane.y = 0;
	game->look_dir = rotate_vector(game->look_dir, deg_to_rad(2));
	game->plane = rotate_vector(game->plane, deg_to_rad(2));
	game->mlx = mlx_init(screenWidth, screenHeight, "cub3d", false);
	// collision_detection(game, );
	mlx_key_hook(game->mlx, &key_hook, game);
	mlx_cursor_hook(game->mlx, &mouse_hook, game);
	mlx_loop_hook(game->mlx, &loop_hook, game);
	mlx_loop(game->mlx);
}
