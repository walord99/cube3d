/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:48:14 by bplante           #+#    #+#             */
/*   Updated: 2024/05/23 00:49:03 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_delta_dist(t_raycaster *ri)
{
	if (ri->ray_dir.x == 0)
		ri->delta_dist.x = DBL_MAX;
	else
		ri->delta_dist.x = dbl_abs(1 / ri->ray_dir.x);
	if (ri->ray_dir.y == 0)
		ri->delta_dist.y = DBL_MAX;
	else
		ri->delta_dist.y = dbl_abs(1 / ri->ray_dir.y);
}

void	get_step_and_side(t_raycaster *ri)
{
	if (ri->ray_dir.x < 0)
	{
		ri->step.x = -1;
		ri->side_dist.x = (ri->start_pos.x - ri->map_pos.x) * ri->delta_dist.x;
	}
	else
	{
		ri->step.x = 1;
		ri->side_dist.x = (1 + ri->map_pos.x - ri->start_pos.x)
			* ri->delta_dist.x;
	}
	if (ri->ray_dir.y < 0)
	{
		ri->step.y = -1;
		ri->side_dist.y = (ri->start_pos.y - ri->map_pos.y) * ri->delta_dist.y;
	}
	else
	{
		ri->step.y = 1;
		ri->side_dist.y = (1 + ri->map_pos.y - ri->start_pos.y)
			* ri->delta_dist.y;
	}
}

void	step(t_raycaster *ri)
{
	if (ri->side_dist.x < ri->side_dist.y)
	{
		ri->side_dist.x += ri->delta_dist.x;
		ri->map_pos.x += ri->step.x;
		ri->side = 0;
	}
	else
	{
		ri->side_dist.y += ri->delta_dist.y;
		ri->map_pos.y += ri->step.y;
		ri->side = 1;
	}
}

void	set_dda_result(t_raycaster *ri, t_dbl_vector *hit_loc)
{
	if (ri->side == 0)
		ri->perp_wall_dist = ri->side_dist.x - ri->delta_dist.x;
	else
		ri->perp_wall_dist = ri->side_dist.y - ri->delta_dist.y;
	if (ri->side == 0)
		ri->wall_x = ri->start_pos.y + ri->perp_wall_dist * ri->ray_dir.y;
	else
		ri->wall_x = ri->start_pos.x + ri->perp_wall_dist * ri->ray_dir.x;
	if (ri->side == 1)
	{
		hit_loc->x = ri->wall_x;
		hit_loc->y = ri->map_pos.y - ri->step.y * clamp(0, 1, -ri->step.y);
	}
	else
	{
		hit_loc->y = ri->wall_x;
		hit_loc->x = ri->map_pos.x - ri->step.x * clamp(0, 1, -ri->step.x);
	}
	ri->wall_x -= floor(ri->wall_x);
}

void	set_door_hit_info(t_raycaster *ri, t_dbl_vector *hit_loc, t_door *door)
{
	if (ri->side == 0)
	{
		if (ri->step.x > 0)
			ri->wall_x = ri->wall_x + door->open_track * -ri->step.x;
		else
			ri->wall_x = ri->wall_x + door->open_track * ri->step.x;
		hit_loc->x += 0.5 * ri->step.x;
	}
	else
	{
		if (ri->step.y > 0)
			ri->wall_x = ri->wall_x + door->open_track * -ri->step.y;
		else
			ri->wall_x = ri->wall_x + door->open_track * ri->step.y;
		hit_loc->x += 0.5 * ri->step.y;
	}
}
