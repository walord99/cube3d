/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:20:44 by bplante           #+#    #+#             */
/*   Updated: 2024/05/14 16:41:39 by bplante          ###   ########.fr       */
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
int	cast_aabb_rays(t_raycaster *rays, t_dbl_vector *hitloc, t_game *game)
{
	int		i;
	double	shortest_len;
	int		shortest_index;

	i = 0;
	shortest_len = INFINITY;
	shortest_index = 0;
	while (i < 4)
	{
		hitloc[i] = cast_ray(&rays[i], game);
		if (rays[i].perp_wall_dist < shortest_len)
		{
			shortest_index = i;
			shortest_len = rays[i].perp_wall_dist;
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
		rays[i].do_doors = false;
		rays[i].ray_dir = dir;
		rays[i].start_pos = add_vector(pos, corner_pos[i]);
		i++;
	}
}

struct				s_c2
{
	t_dbl_vector	*mov;
	t_dbl_vector	*mov_dir;
	t_raycaster		*shortest;
	t_dbl_vector	new_pos;
	double			*move_len;
};

void	float_fix(t_raycaster *shortest, t_dbl_vector *newpos)
{
	if (shortest->side == 1)
		newpos->y -= 0.0001 * shortest->step.y;
	else
		newpos->x -= 0.0001 * shortest->step.x;
}

void	collision_2(t_game *game, struct s_c2 a)
{
	if (a.shortest->side == 1)
	{
		a.mov_dir->x = a.shortest->step.x;
		a.mov_dir->y = 0;
		*a.move_len = dbl_abs(a.mov->x) - dbl_abs(game->pos.x - a.new_pos.x);
		a.mov->x = *a.move_len * a.mov_dir->x;
		a.mov->y = 0;
	}
	else
	{
		a.mov_dir->x = 0;
		a.mov_dir->y = a.shortest->step.y;
		*a.move_len = dbl_abs(a.mov->y) - dbl_abs(game->pos.y - a.new_pos.y);
		a.mov->x = 0;
		a.mov->y = *a.move_len * a.mov_dir->y;
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
	init_aabb_rays(ray_info, game->pos, game->aabb_corners, movement_dir);
	shortest_ray = cast_aabb_rays(ray_info, hitloc, game);
	if (ray_info[shortest_ray].perp_wall_dist > move_len)
		return (add_vector(game->pos, movement));
	newpos = add_vector(hitloc[shortest_ray],
			multiply_vector(game->aabb_corners[shortest_ray], -1));
	float_fix(&ray_info[shortest_ray], &newpos);
	collision_2(game, (struct s_c2){.mov = &movement, .mov_dir = &movement_dir,
		.move_len = &move_len, .new_pos = newpos,
		.shortest = &ray_info[shortest_ray]});
	init_aabb_rays(ray_info, newpos, game->aabb_corners, movement_dir);
	shortest_ray = cast_aabb_rays(ray_info, hitloc, game);
	if (ray_info[shortest_ray].perp_wall_dist > move_len)
		return (add_vector(newpos, movement));
	newpos = add_vector(hitloc[shortest_ray],
			multiply_vector(game->aabb_corners[shortest_ray], -1));
	float_fix(&ray_info[shortest_ray], &newpos);
	return (newpos);
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
	mlx_get_mouse_pos(game->mlx, &game->mouse_pos.x, &game->mouse_pos.y);
	game->mouse_pos.x = game->mouse_pos.x - SCREENWIDTH / 2;
	game->mouse_pos.y = game->mouse_pos.y - SCREENHEIGHT / 2;
	mlx_set_mouse_pos(game->mlx, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	rotate_player(game, game->mouse_pos.x / 20);
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
