/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:49:31 by yothmani          #+#    #+#             */
/*   Updated: 2024/04/25 15:10:28 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_map	*init_map_struct(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->grid = NULL;
	map->height = 0;
	map->width = 0;
	map->first_map_line = -1;
	map->has_direction = false;
	map->spawn_direction = 0;
	map->spawn_x = -1;
	map->spawn_y = -1;
	map->checked_element = (t_element_check){
		.f_color = false,
		.c_color = false,
		.texture_no = false,
		.texture_so = false,
		.texture_we = false,
		.texture_ea = false,
	};
	return (map);
}

bool	is_char_valid(char **str, t_map *map)
{
	if (!validate_grid_characters(str, map))
		return (false);
	if (!handle_start_points(str, map))
		return (false);
	return (true);
}

int	colonne_check(char **str, t_map map)
{
	int	x;
	int	y;
	int	end;

	if (!str)
		return (0);
	x = 0;
	while (x < map.height)
	{
		y = 0;
		while (is_white_space(str[x][y]))
			y++;
		if (check_col_start(str, x, y))
			return (1);
		end = map.width;
		while (end > 0 && is_white_space(str[x][end - 1]))
			end--;
		if (check_col_end(str, x, end))
			return (1);
		x++;
	}
	return (0);
}

int	first_and_last_line_check(char **str, t_map map)
{
	if (!str)
		return (0);
	if (check_first_and_last_line(str, map) != 0)
		return (1);
	return (0);
}

bool	is_map_valid(char **str, t_map *map)
{
	if (!is_char_valid(str, map))
		return (false);
	if (colonne_check(str, *map))
		return (false);
	if (first_and_last_line_check(str, *map))
		return (false);
	return (true);
}
