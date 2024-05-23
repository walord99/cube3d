/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:51:07 by bplante           #+#    #+#             */
/*   Updated: 2024/05/23 11:49:12 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_texture_color(unsigned int x, unsigned int y,
		mlx_texture_t *tex)
{
	uint8_t	*byte;

	if (y >= tex->height - 1)
		y = tex->height - 2;
	if (x >= tex->width - 1)
		x = tex->width - 2;
	byte = &tex->pixels[(y * tex->width + (x * -1 + tex->width))
		* tex->bytes_per_pixel];
	return (rbga_builder(byte[0], byte[1], byte[2], byte[3]));
}

void	get_pixel_color(t_int_vector pixel_pos, t_int_vector center,
		t_game *game)
{
	t_dbl_vector	relpos;
	t_dbl_vector	pos;
	t_dbl_vector	*rot_pre;
	char			tile;

	rot_pre = game->minimap.norm_rot;
	relpos.x = (pixel_pos.x - center.x) * 0.05;
	relpos.y = (pixel_pos.y - center.y) * 0.05;
	pos = add_vector(add_vector(multiply_vector(rot_pre[0], relpos.x),
				multiply_vector(rot_pre[1], relpos.y)), game->pos);
	tile = get_map_loc((int)pos.x, (int)pos.y, &game->map);
	if (tile == '1')
		mlx_put_pixel(game->minimap.render, pixel_pos.x, pixel_pos.y,
			rbga_builder(0, 0, 0, 255));
	else if (tile == '-' || tile == '|')
		mlx_put_pixel(game->minimap.render, pixel_pos.x, pixel_pos.y,
			rbga_builder(0, 0, 0, 150));
}

uint32_t	rbga_builder(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
