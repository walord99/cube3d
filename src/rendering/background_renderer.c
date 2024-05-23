/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_renderer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:54:48 by bplante           #+#    #+#             */
/*   Updated: 2024/05/23 01:03:07 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_square(mlx_image_t *img, uint32_t color, t_int_vector start,
		t_int_vector end)
{
	int	temp;

	temp = start.y;
	while (start.x != end.x)
	{
		start.y = temp;
		while (start.y != end.y)
		{
			mlx_put_pixel(img, start.x, start.y, color);
			start.y++;
		}
		start.x++;
	}
}

mlx_image_t	*create_floor_ceil_image(t_game *game)
{
	mlx_image_t		*fc_img;
	t_int_vector	start;
	t_int_vector	end;

	fc_img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	start.x = 0;
	start.y = 0;
	end.x = SCREENWIDTH;
	end.y = SCREENHEIGHT / 2;
	fill_square(fc_img, game->map.cieling, start, end);
	start.y = SCREENHEIGHT / 2;
	start.x = 0;
	end.x = SCREENWIDTH;
	end.y = SCREENHEIGHT;
	fill_square(fc_img, game->map.floor, start, end);
	return (fc_img);
}
