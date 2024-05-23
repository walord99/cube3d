/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:40:54 by bplante           #+#    #+#             */
/*   Updated: 2024/05/23 01:04:10 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	float_fix(t_raycaster *shortest, t_dbl_vector *newpos)
{
	if (shortest->side == 1)
		newpos->y -= 0.0001 * shortest->step.y;
	else
		newpos->x -= 0.0001 * shortest->step.x;
}

void	collision_2(t_game *game, t_c2_vars a)
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

	move_len = sqrt(pow(movement.x, 2) + pow(movement.y, 2));
	init_aabb_rays(ray_info, game->pos, game->aabb_corners, movement_dir);
	shortest_ray = cast_aabb_rays(ray_info, hitloc, game);
	if (ray_info[shortest_ray].perp_wall_dist > move_len)
		return (add_vector(game->pos, movement));
	newpos = add_vector(hitloc[shortest_ray],
			multiply_vector(game->aabb_corners[shortest_ray], -1));
	float_fix(&ray_info[shortest_ray], &newpos);
	collision_2(game, (t_c2_vars){.mov = &movement, .mov_dir = &movement_dir,
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
