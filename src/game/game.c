/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:20:44 by bplante           #+#    #+#             */
/*   Updated: 2024/04/19 14:06:07 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook(mlx_key_data_t key_data, void *param)
{
	t_game	*game;

	game = (t_game *)param;
}

void	collision_detection(t_vector movement, t_game *game)
{
	double		cameraX;
	int			mapX;
	int			mapY;
	t_vector	sideDist;
	t_vector	deltaDist;
	t_vector	newpos;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			x;
	int			y;

	newpos = add_vector(game->pos, movement);
	mapX = game->pos.x / 1;
	mapY = game->pos.y / 1;
	if (movement.x == 0)
		deltaDist.x = DBL_MAX;
	else
		deltaDist.x = dbl_abs(1 / movement.x);
	if (movement.y == 0)
		deltaDist.y = DBL_MAX;
	else
		deltaDist.y = dbl_abs(1 / movement.y);
	if (movement.x < 0)
	{
		stepX = -1;
		sideDist.x = (game->pos.x - mapX - PLAYER_MOVE_BOX) * deltaDist.x;
	}
	else
	{
		stepX = 1;
		sideDist.x = (1 + mapX - game->pos.x - PLAYER_MOVE_BOX) * deltaDist.x;
	}
	if (movement.y < 0)
	{
		stepY = -1;
		sideDist.y = (game->pos.y - mapY - PLAYER_MOVE_BOX) * deltaDist.y;
	}
	else
	{
		stepY = 1;
		sideDist.y = (1 + mapY - game->pos.y - PLAYER_MOVE_BOX) * deltaDist.y;
	}
	hit = 0;
	while (hit == 0)
	{
		if (sideDist.x < sideDist.y)
		{
			sideDist.x += deltaDist.x;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDist.y += deltaDist.y;
			mapY += stepY;
			side = 1;
		}
		if (get_map_coordinate(mapX, mapY, game->map) != 0)
			hit = 1;
	}
	if (side == 0)
		perpWallDist = sideDist.x - deltaDist.x;
	else
		perpWallDist = sideDist.y - deltaDist.y;
	double mag = magnetude(movement);
	if (perpWallDist < mag)
	{
		int test = 1;
	}
}

void	mouse_hook(double xpos, double ypos, void *param)
{
	// printf("x: %f\ny: %f\n", xpos, ypos);
}

void	loop_hook(void *param)
{
	t_game		*game;
	t_vector	movement;
	double		move_speed;
	double		rot_speed;
	int			mapX;
	int			mapY;
	t_vector	temp_pos;
	double		x_offset;
	double		y_offset;

	game = (t_game *)param;
	movement.x = 0;
	movement.y = 0;
	move_speed = game->mlx->delta_time * 3.0;
	rot_speed = game->mlx->delta_time * 90.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		movement = add_vector(movement, game->look_dir);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		movement = add_vector(movement, multiply_vector(game->look_dir, -1));
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		movement = add_vector(movement, rotate_vector(game->look_dir,
					deg_to_rad(-90)));
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		movement = add_vector(movement, rotate_vector(game->look_dir,
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
	movement = round_off_floating_point_errors(movement);
	movement = normalise_vector(movement);
	collision_detection(movement, game);
	movement = multiply_vector(movement, move_speed);
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
	// if (get_map_coordinate((int)(temp_pos.x + x_offset), mapY, game->map) != 0)
	// {
	// 	if (x_offset > 0)
	// 		temp_pos.x -= temp_pos.x - (mapX + 1) + x_offset;
	// 	else
	// 		temp_pos.x -= temp_pos.x - mapX + x_offset;
	// }
	// if (get_map_coordinate(mapX, (int)(temp_pos.y + y_offset), game->map) != 0)
	// {
	// 	if (y_offset > 0)
	// 		temp_pos.y -= temp_pos.y - (mapY + 1) + y_offset;
	// 	else
	// 		temp_pos.y -= temp_pos.y - mapY + y_offset;
	// }
	game->pos = add_vector(game->pos, movement);
	printf("x:%f\ty:%f\n", game->pos.x, game->pos.y);
	mlx_delete_image(game->mlx, game->rendered);
	game->rendered = mlx_new_image(game->mlx, screenWidth, screenWidth);
	cast_rays(game);
	mlx_image_to_window(game->mlx, game->rendered, 0, 0);
}

void	init_game(t_game *game)
{
	game->pos.x = 1.5;
	game->pos.y = 3.2;
	game->look_dir.x = 0;
	game->look_dir.y = -1;
	game->plane.x = 1;
	game->plane.y = 0;
	game->look_dir = rotate_vector(game->look_dir, deg_to_rad(90));
	game->plane = rotate_vector(game->plane, deg_to_rad(90));
	game->mlx = mlx_init(screenWidth, screenHeight, "cub3d", false);
	mlx_key_hook(game->mlx, &key_hook, game);
	mlx_cursor_hook(game->mlx, &mouse_hook, game);
	mlx_loop_hook(game->mlx, &loop_hook, game);
	mlx_loop(game->mlx);
}
