/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_accessor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:48:26 by bplante           #+#    #+#             */
/*   Updated: 2024/05/23 00:25:14 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	get_map_loc(unsigned int x, unsigned int y, t_map *map)
{
	if (x > map->width - 1 || y > map->height - 1)
		return (false);
	return (map->grid[y][x]);
}
