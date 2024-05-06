/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:20:44 by bplante           #+#    #+#             */
/*   Updated: 2024/05/06 10:40:40 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cast_aabb_rays(t_raycaster *rays, t_dbl_vector *hitloc, t_map *map)
{
	int		i;
	double	shortest_len;
	int		shortest_index;

	i = 0;
	shortest_len = INFINITY;
	shortest_index = 0;
	while (i < 4)
	{
		hitloc[i] = cast_ray(&rays[i], map);
		if (rays[i].perpWallDist < shortest_len)
		{
			shortest_index = i;
			shortest_len = rays[i].perpWallDist;
		}
		i++;
	}
	return (shortest_index);
}

void	init_aabb_rays(t_raycaster *rays, t_dbl_vector pos,
		t_dbl_vector *corner_pos, t_dbl_vector dir)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		rays[i].rayDir = dir;
		rays[i].start_pos = add_vector(pos, corner_pos[i]);
		i++;
	}
}

t_dbl_vector	collision_detection(t_game *game, t_dbl_vector movement,
		t_dbl_vector movement_dir)
{
	t_raycaster		ray_info[4];
	t_dbl_vector	newpos;
	t_dbl_vector	hitloc[4];
	double			move_len;
	int				shortest_ray;

	move_len = magnetude(movement);
	init_aabb_rays(ray_info, game->pos, game->AABB_corners, movement_dir);
	shortest_ray = cast_aabb_rays(ray_info, hitloc, &game->map);
	if (ray_info[shortest_ray].perpWallDist > move_len)
		return (add_vector(game->pos, movement));
	newpos = add_vector(hitloc[shortest_ray], multiply_vector(game->AABB_corners[shortest_ray], -1));
	if (ray_info[shortest_ray].side == 1)
		newpos.y -= 0.000000001 * ray_info[shortest_ray].step.y;
	else if (ray_info[shortest_ray].side == 0)
		newpos.x -= 0.000000001 * ray_info[shortest_ray].step.x;
	if (ray_info[shortest_ray].side == 1)
	{
		movement_dir.x = ray_info[shortest_ray].step.x;
		movement_dir.y = 0;
		move_len = dbl_abs(movement.x) - dbl_abs(game->pos.x - newpos.x);
		movement.x = move_len * movement_dir.x;
		movement.y = 0;
	}
	else
	{
		movement_dir.x = 0;
		movement_dir.y = ray_info[shortest_ray].step.y;
		move_len = dbl_abs(movement.y) - dbl_abs(game->pos.y - newpos.y);
		movement.x = 0;
		movement.y = move_len * movement_dir.y;
	}
	init_aabb_rays(ray_info, newpos, game->AABB_corners, movement_dir);
	shortest_ray = cast_aabb_rays(ray_info, hitloc, &game->map);
	if (ray_info[shortest_ray].perpWallDist > move_len)
		return add_vector(newpos, movement);
	newpos = add_vector(hitloc[shortest_ray], multiply_vector(game->AABB_corners[shortest_ray], -1));
	if (ray_info[shortest_ray].side == 1)
		newpos.y -= 0.000000001 * ray_info[shortest_ray].step.y;
	else if (ray_info[shortest_ray].side == 0)
		newpos.x -= 0.000000001 * ray_info[shortest_ray].step.x;
	return (newpos);
}

void	loop_hook(void *param)
{
	t_game			*game;
	t_dbl_vector	movement_dir;
	double			move_speed;
	double			rot_speed;
	t_dbl_vector	movement;

	game = (t_game *)param;
	mlx_get_mouse_pos(game->mlx, &game->mouse_pos.x, &game->mouse_pos.y);
	game->mouse_pos.x = game->mouse_pos.x - screenWidth / 2;
	game->mouse_pos.y = game->mouse_pos.y - screenHeight / 2;
	printf("x: %i y:%i\n", game->mouse_pos.x, game->mouse_pos.y);
	mlx_set_mouse_pos(game->mlx, screenWidth / 2, screenHeight / 2);	
	movement_dir.x = 0;
	movement_dir.y = 0;
	move_speed = game->mlx->delta_time * 3.0;
	rot_speed = game->mlx->delta_time * 90.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
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

	game->look_dir = rotate_vector(game->look_dir, deg_to_rad(game->mouse_pos.x * rot_speed / 20));
	game->plane = rotate_vector(game->plane, deg_to_rad(game->mouse_pos.x * rot_speed / 20));
	movement_dir = round_off_floating_point_errors(movement_dir);
	movement_dir = normalise_vector(movement_dir);
	movement = multiply_vector(movement_dir, move_speed);
	game->pos = collision_detection(game, movement, movement_dir);
	printf("x:%f\ty:%f\n", game->pos.x, game->pos.y);
	mlx_delete_image(game->mlx, game->rendered);
	game->rendered = mlx_new_image(game->mlx, screenWidth, screenWidth);
	draw(game);
	mlx_image_to_window(game->mlx, game->rendered, 0, 0);
}
