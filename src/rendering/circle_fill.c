/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:51:47 by bplante           #+#    #+#             */
/*   Updated: 2024/05/23 00:52:06 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	itterate_fill(t_int_vector pos, t_int_vector center, t_game *game)
{
	int	dir;

	dir = -1;
	if (pos.x < center.x)
		dir = 1;
	while (pos.x != center.x)
	{
		get_pixel_color(pos, center, game);
		pos.x += dir;
	}
	if (dir == 1)
		get_pixel_color(pos, center, game);
}

void	mirror_8(t_mpcf *p, int center_x, int center_y, t_game *game)
{
	itterate_fill((t_int_vector){.x = center_x - p->x, .y = center_y - p->y},
		(t_int_vector){.x = center_x, .y = center_y}, game);
	itterate_fill((t_int_vector){.x = center_x + p->x, .y = center_y - p->y},
		(t_int_vector){.x = center_x, .y = center_y}, game);
	itterate_fill((t_int_vector){.x = center_x - p->x, .y = center_y + p->y},
		(t_int_vector){.x = center_x, .y = center_y}, game);
	itterate_fill((t_int_vector){.x = center_x + p->x, .y = center_y + p->y},
		(t_int_vector){.x = center_x, .y = center_y}, game);
	itterate_fill((t_int_vector){.x = center_x - p->y, .y = center_y - p->x},
		(t_int_vector){.x = center_x, .y = center_y}, game);
	itterate_fill((t_int_vector){.x = center_x + p->y, .y = center_y - p->x},
		(t_int_vector){.x = center_x, .y = center_y}, game);
	itterate_fill((t_int_vector){.x = center_x - p->y, .y = center_y + p->x},
		(t_int_vector){.x = center_x, .y = center_y}, game);
	itterate_fill((t_int_vector){.x = center_x + p->y, .y = center_y + p->x},
		(t_int_vector){.x = center_x, .y = center_y}, game);
}

void	mid_point_circle_fill(int center_x, int center_y, int r, t_game *game)
{
	t_mpcf	p;

	p.r2 = r + r;
	p.x = r;
	p.y = 0;
	p.delta_y = -2;
	p.delta_x = p.r2 + p.r2 - 4;
	p.d = p.r2 - 1;
	while (p.y <= p.x)
	{
		mirror_8(&p, center_x, center_y, game);
		p.d += p.delta_y;
		p.delta_y -= 4;
		p.y++;
		if (p.d < 0)
		{
			p.d += p.delta_x;
			p.delta_x -= 4;
			p.x--;
		}
	}
}
