/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_accessor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:48:26 by bplante           #+#    #+#             */
/*   Updated: 2024/05/08 16:58:45 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char get_map_coordinate(int x, int y, t_map *map)
{
    if (x < 0 || y < 0 || x > map->width - 1 || y > map->height - 1)
        return false;
    return map->grid[y][x];
}