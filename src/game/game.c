/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:20:44 by bplante           #+#    #+#             */
/*   Updated: 2024/04/30 02:09:01 by bplante          ###   ########.fr       */
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

t_dbl_vector	collision_detection(t_game *game,
		t_dbl_vector movement)
{
	int			mapX;
	int			mapY;
	t_dbl_vector	newpos;
	t_dbl_vector	relpos;
	int			sideX;
	int			sideY;

	newpos = add_vector(game->pos, movement);
	mapX = (int)newpos.x;
	mapY = (int)newpos.y;
	sideX = 0;
	sideY = 0;
	relpos.x = newpos.x - mapX;
	relpos.y = newpos.y - mapY;
	if (relpos.x < PLAYER_MOVE_BOX)
		sideX = -1;
	else if (relpos.x > 1 - PLAYER_MOVE_BOX)
	{
		sideX = 1;
		relpos.x = dbl_abs(relpos.x - 1);
	}
	if (relpos.y < PLAYER_MOVE_BOX)
		sideY = -1;
	else if (relpos.y > 1 - PLAYER_MOVE_BOX)
	{
		sideY = 1;
		relpos.y = dbl_abs(relpos.y - 1);
	}

	if (get_map_coordinate(mapX + sideX, mapY, game->map))
		newpos.x = dbl_abs(PLAYER_MOVE_BOX - clamp(0, 1, sideX)) + mapX;
	if (get_map_coordinate(mapX, mapY + sideY, game->map))
		newpos.y = dbl_abs(PLAYER_MOVE_BOX - clamp(0, 1, sideY)) + mapY;

	if (abs(sideX) == abs(sideY))
	{
		if (get_map_coordinate(mapX + sideX, mapY + sideY, game->map))
		{
			if (relpos.x < relpos.y)
			{
				newpos.y = dbl_abs(PLAYER_MOVE_BOX - clamp(0, 1, sideY)) + mapY;
			}
			else
				newpos.x = dbl_abs(PLAYER_MOVE_BOX - clamp(0, 1, sideX)) + mapX;
		}
	}

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
	game->pos =  collision_detection(game, movement);
	// mapX = (int)game->pos.x;
	// mapY = (int)game->pos.y;
	// temp_pos = add_vector(game->pos, movement);
	// if (movement.x < 0)
	// 	x_offset = -PLAYER_MOVE_BOX;
	// else
	// 	x_offset = PLAYER_MOVE_BOX;
	// if (movement.y < 0)
	// 	y_offset = -PLAYER_MOVE_BOX;
	// else
	// 	y_offset = PLAYER_MOVE_BOX;
	// if (get_map_coordinate((int)(temp_pos.x + x_offset), mapY,
	//		game->map) != 0)
	// {
	// 	if (x_offset > 0)
	// 		temp_pos.x -= temp_pos.x - (mapX + 1) + x_offset;
	// 	else
	// 		temp_pos.x -= temp_pos.x - mapX + x_offset;
	// }
	// if (get_map_coordinate(mapX, (int)(temp_pos.y + y_offset),
	//		game->map) != 0)
	// {
	// 	if (y_offset > 0)
	// 		temp_pos.y -= temp_pos.y - (mapY + 1) + y_offset;
	// 	else
	// 		temp_pos.y -= temp_pos.y - mapY + y_offset;
	// }
	
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
	game->pos.x = 5;
	game->pos.y = 5;
	game->look_dir.x = 0;
	game->look_dir.y = -1;
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
