/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:42:50 by bplante           #+#    #+#             */
/*   Updated: 2024/05/14 11:27:56 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_delta_dist(t_raycaster *ri)
{
	if (ri->rayDir.x == 0)
		ri->deltaDist.x = DBL_MAX;
	else
		ri->deltaDist.x = dbl_abs(1 / ri->rayDir.x);
	if (ri->rayDir.y == 0)
		ri->deltaDist.y = DBL_MAX;
	else
		ri->deltaDist.y = dbl_abs(1 / ri->rayDir.y);
}

void	get_step_and_side(t_raycaster *ri)
{
	double	relpos;

	if (ri->rayDir.x < 0)
	{
		ri->step.x = -1;
		relpos = ri->start_pos.x - ri->map_pos.x;
		ri->sideDist.x = (relpos)*ri->deltaDist.x;
	}
	else
	{
		ri->step.x = 1;
		relpos = 1 + ri->map_pos.x - ri->start_pos.x;
		ri->sideDist.x = (relpos)*ri->deltaDist.x;
	}
	if (ri->rayDir.y < 0)
	{
		ri->step.y = -1;
		relpos = ri->start_pos.y - ri->map_pos.y;
		ri->sideDist.y = (relpos)*ri->deltaDist.y;
	}
	else
	{
		ri->step.y = 1;
		relpos = 1 + ri->map_pos.y - ri->start_pos.y;
		ri->sideDist.y = (relpos)*ri->deltaDist.y;
	}
}

// void	dda_continue(t_raycaster *ri, t_map *map)
// {
// }

void	dda_loop(t_raycaster *ri, t_game *game)
{
	t_door	*door;

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
		door = get_door(ri->map_pos.x, ri->map_pos.y, game);
		if (get_map_coordinate(ri->map_pos.x, ri->map_pos.y, &game->map) == '|'
			&& ri->do_doors)
		{
			if (ri->sideDist.x - ri->deltaDist.x / 2 < ri->sideDist.y)
			{
				ri->sideDist.x -= ri->deltaDist.x / 2;
				ri->sideDist.x += ri->deltaDist.x;
				ri->side = 0;
				return ;
			}
		}
		else if (get_map_coordinate(ri->map_pos.x, ri->map_pos.y,
				&game->map) == '-' && ri->do_doors)
		{
			if (ri->sideDist.y - ri->deltaDist.y / 2 < ri->sideDist.x)
			{
				ri->sideDist.y -= ri->deltaDist.y / 2;
				ri->sideDist.y += ri->deltaDist.y;
				ri->side = 1;
				return ;
			}
		}
		else if (get_map_coordinate(ri->map_pos.x, ri->map_pos.y,
				&game->map) == '1' || (door && door->open_track < 1))
			return ;
	}
}

t_dbl_vector	cast_ray(t_raycaster *ri, t_game *game)
{
	t_dbl_vector	hit_loc;
	t_door			*door;

	door = (t_door *)1;
	ri->map_pos.x = ri->start_pos.x / 1;
	ri->map_pos.y = ri->start_pos.y / 1;
	get_delta_dist(ri);
	get_step_and_side(ri);
	while (door)
	{
		dda_loop(ri, game);
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
			hit_loc.x = ri->wallX;
			hit_loc.y = ri->map_pos.y - ri->step.y * clamp(0, 1, -ri->step.y);
		}
		else
		{
			hit_loc.y = ri->wallX;
			hit_loc.x = ri->map_pos.x - ri->step.x * clamp(0, 1, -ri->step.x);
		}
		ri->wallX -= floor(ri->wallX);
		door = get_door(ri->map_pos.x, ri->map_pos.y, game);
		if (door != NULL && ri->do_doors)
		{
			if (ri->wallX < door->open_track)
			{
				if (ri->side == 0)
					ri->sideDist.x -= ri->deltaDist.x / 2;
				else
					ri->sideDist.y -= ri->deltaDist.y / 2;
			}
			else
			{
				if (ri->side == 0)
				{
					if (ri->step.x > 0)
						ri->wallX = ri->wallX + door->open_track * -ri->step.x;
					else
						ri->wallX = ri->wallX + door->open_track * ri->step.x;
					hit_loc.x += 0.5 * ri->step.x;
				}
				else
				{

					if (ri->step.y > 0)
						ri->wallX = ri->wallX + door->open_track * -ri->step.y;
					else
						ri->wallX = ri->wallX + door->open_track * ri->step.y;
					hit_loc.x += 0.5 * ri->step.y;
				}
				door = NULL;
			}
		}
		else
			door = NULL;
	}
	return (hit_loc);
}
