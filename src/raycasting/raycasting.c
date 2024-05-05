/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:42:50 by bplante           #+#    #+#             */
/*   Updated: 2024/05/02 16:13:58 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_delta_dist(t_raycaster *ri)
{
	t_dbl_vector	deltaDist;

	if (ri->rayDir.x == 0)
		ri->deltaDist.x = DBL_MAX;
	else
		ri->deltaDist.x = dbl_abs(1 / ri->rayDir.x);
	if (ri->rayDir.y == 0)
		ri->deltaDist.y = DBL_MAX;
	else
		ri->deltaDist.y = dbl_abs(1 / ri->rayDir.y);
}

void	get_step_and_side(t_raycaster *ri, t_map *map)
{
	if (ri->rayDir.x < 0)
	{
		ri->step.x = -1;
		ri->sideDist.x = (ri->start_pos.x - ri->map_pos.x) * ri->deltaDist.x;
	}
	else
	{
		ri->step.x = 1;
		ri->sideDist.x = (1 + ri->map_pos.x - ri->start_pos.x)
			* ri->deltaDist.x;
	}
	if (ri->rayDir.y < 0)
	{
		ri->step.y = -1;
		ri->sideDist.y = (ri->start_pos.y - ri->map_pos.y) * ri->deltaDist.y;
	}
	else
	{
		ri->step.y = 1;
		ri->sideDist.y = (1 + ri->map_pos.y - ri->start_pos.y)
			* ri->deltaDist.y;
	}
}

void	dda_loop(t_raycaster *ri, t_map *map)
{
	while (true)
	{
		if (ri->sideDist.x < ri->sideDist.y)
		{
			ri->sideDist.x += ri->deltaDist.x;
			ri->map_pos.x += ri->step.x;
			ri->side = 0;
		}
		else
		{
			ri->sideDist.y += ri->deltaDist.y;
			ri->map_pos.y += ri->step.y;
			ri->side = 1;
		}
		if (get_map_coordinate(ri->map_pos.x, ri->map_pos.y, map))
			return ;
	}
}

t_dbl_vector	cast_ray(t_raycaster *ri, t_map *map)
{
	t_dbl_vector	hit_loc;

	ri->map_pos.x = ri->start_pos.x / 1;
	ri->map_pos.y = ri->start_pos.y / 1;
	get_delta_dist(ri);
	get_step_and_side(ri, map);
	dda_loop(ri, map);
	if (ri->side == 0)
		ri->perpWallDist = ri->sideDist.x - ri->deltaDist.x;
	else
		ri->perpWallDist = ri->sideDist.y - ri->deltaDist.y;
	if (ri->side == 0)
		ri->wallX = ri->start_pos.y + ri->perpWallDist * ri->rayDir.y;
	else
		ri->wallX = ri->start_pos.x + ri->perpWallDist * ri->rayDir.x;
	if (ri->side == 1)
	{
		ri->map_pos.y -= ri->step.y * clamp(0, 1, -ri->step.y);
		hit_loc.x = ri->wallX;
		hit_loc.y = ri->map_pos.y;
	}
	else
	{
		ri->map_pos.x -= ri->step.x * clamp(0, 1, -ri->step.x);
		hit_loc.y = ri->wallX;
		hit_loc.x = ri->map_pos.x;
	}
	ri->wallX -= floor(ri->wallX);
	return (hit_loc);
}