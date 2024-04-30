/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:42:50 by bplante           #+#    #+#             */
/*   Updated: 2024/04/30 02:43:36 by bplante          ###   ########.fr       */
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

void	get_step_and_side(t_raycaster *ri, t_game *game)
{
	if (ri->rayDir.x < 0)
	{
		ri->step.x = -1;
		ri->sideDist.x = (game->pos.x - ri->map_pos.x) * ri->deltaDist.x;
	}
	else
	{
		ri->step.x = 1;
		ri->sideDist.x = (1 + ri->map_pos.x - game->pos.x) * ri->deltaDist.x;
	}
	if (ri->rayDir.y < 0)
	{
		ri->step.y = -1;
		ri->sideDist.y = (game->pos.y - ri->map_pos.y) * ri->deltaDist.y;
	}
	else
	{
		ri->step.y = 1;
		ri->sideDist.y = (1 + ri->map_pos.y - game->pos.y) * ri->deltaDist.y;
	}
}

void	dda_loop(t_raycaster *ri, t_game *game)
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
		if (get_map_coordinate(ri->map_pos.x, ri->map_pos.y, game->map))
			return ;
	}
}

void	cast_ray(t_raycaster *ri, t_game *game)
{
	ri->map_pos.x = game->pos.x / 1;
	ri->map_pos.y = game->pos.y / 1;
	get_delta_dist(ri);
	get_step_and_side(ri, game);
	dda_loop(ri, game);
	if (ri->side == 0)
		ri->perpWallDist = ri->sideDist.x - ri->deltaDist.x;
	else
		ri->perpWallDist = ri->sideDist.y - ri->deltaDist.y;
	if (ri->side == 0)
		ri->wallX = game->pos.y + ri->perpWallDist * ri->rayDir.y;
	else
		ri->wallX = game->pos.x + ri->perpWallDist * ri->rayDir.x;
	ri->wallX -= floor(ri->wallX);
}