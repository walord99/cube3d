/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:42:50 by bplante           #+#    #+#             */
/*   Updated: 2024/05/23 00:49:45 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_door_distance_hori(t_raycaster *ri)
{
	if (ri->side_dist.y - ri->delta_dist.y / 2 < ri->side_dist.x)
	{
		ri->side_dist.y -= ri->delta_dist.y / 2;
		ri->side_dist.y += ri->delta_dist.y;
		ri->side = 1;
		return (1);
	}
	return (0);
}

int	set_door_distance_vert(t_raycaster *ri)
{
	if (ri->side_dist.x - ri->delta_dist.x / 2 < ri->side_dist.y)
	{
		ri->side_dist.x -= ri->delta_dist.x / 2;
		ri->side_dist.x += ri->delta_dist.x;
		ri->side = 0;
		return (1);
	}
	return (0);
}

void	dda_loop(t_raycaster *ri, t_game *game)
{
	t_door	*door;

	while (true)
	{
		step(ri);
		door = get_door(ri->map_pos.x, ri->map_pos.y, game);
		if (get_map_loc(ri->map_pos.x, ri->map_pos.y, &game->map) == '|'
			&& ri->do_doors)
		{
			if (set_door_distance_vert(ri))
				return ;
		}
		else if (get_map_loc(ri->map_pos.x, ri->map_pos.y, &game->map) == '-'
			&& ri->do_doors)
		{
			if (set_door_distance_hori(ri))
				return ;
		}
		else if (get_map_loc(ri->map_pos.x, ri->map_pos.y, &game->map) == '1'
			|| (door && door->open_track < 1))
			return ;
	}
}

t_door	*door_logic(t_raycaster *ri, t_dbl_vector *hit_loc, t_door *door)
{
	if (ri->wall_x < door->open_track)
	{
		if (ri->side == 0)
			ri->side_dist.x -= ri->delta_dist.x / 2;
		else
			ri->side_dist.y -= ri->delta_dist.y / 2;
		return (door);
	}
	else
	{
		set_door_hit_info(ri, hit_loc, door);
		return (NULL);
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
		set_dda_result(ri, &hit_loc);
		door = get_door(ri->map_pos.x, ri->map_pos.y, game);
		if (door != NULL && ri->do_doors)
			door = door_logic(ri, &hit_loc, door);
		else
			door = NULL;
	}
	return (hit_loc);
}
