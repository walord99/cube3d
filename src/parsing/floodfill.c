/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:14:59 by yothmani          #+#    #+#             */
/*   Updated: 2024/05/23 00:17:24 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_explored_grid(void **grid)
{
	int	i;

	i = 0;
	if (!grid)
		return ;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

bool	**allocate_grid_to_explore(int height, int width)
{
	bool	**visited;
	int		i;

	visited = ft_calloc(height + 1, sizeof(bool *));
	if (!visited)
		return (NULL);
	i = 0;
	while (i < height)
	{
		visited[i] = ft_calloc(width, sizeof(bool));
		if (!visited[i])
		{
			free_explored_grid((void **)visited);
			return (NULL);
		}
		i++;
	}
	visited[i] = 0;
	return (visited);
}

bool	floodfill(t_map *map, bool **is_explored, unsigned int i,
		unsigned int j)
{
	bool	is_playable;

	if (i >= map->height || j >= map->width)
		return (false);
	if (is_explored[i][j] == true || map->grid[i][j] == '1')
		return (true);
	is_explored[i][j] = true;
	is_playable = true;
	is_playable &= floodfill(map, is_explored, i - 1, j);
	is_playable &= floodfill(map, is_explored, i + 1, j);
	is_playable &= floodfill(map, is_explored, i, j - 1);
	is_playable &= floodfill(map, is_explored, i, j + 1);
	return (is_playable);
}

bool	is_door_closed(char **str, t_map *map)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	while (x < map->height)
	{
		y = 0;
		while (y < map->width)
		{
			if (str[x][y] == '-' && (str[x][y + 1] != '1' || str[x][y
					- 1] != '1'))
				return (false);
			if (str[x][y] == '|' && (str[x + 1][y] != '1' || str[x
					- 1][y] != '1'))
				return (false);
			y++;
		}
		x++;
	}
	return (true);
}

bool	is_map_playable(t_map *map)
{
	int		x;
	int		y;
	bool	**is_explored;
	bool	is_playable;

	x = map->spawn_x;
	y = map->spawn_y;
	is_explored = allocate_grid_to_explore(map->height, map->width);
	if (!is_explored)
		return (false);
	if (!is_door_closed(map->grid, map))
		return (false);
	is_playable = floodfill(map, is_explored, y, x);
	free_explored_grid((void **)is_explored);
	if (!is_playable)
		return (false);
	return (true);
}
