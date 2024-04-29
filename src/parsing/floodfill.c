/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:14:59 by yothmani          #+#    #+#             */
/*   Updated: 2024/04/29 16:47:58 by yothmani         ###   ########.fr       */
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

	visited = ft_calloc(height, sizeof(bool *));
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
	return (visited);
}

bool	floodfill(t_map *map, bool **is_explored, int i, int j)
{
	bool	is_playable;

	// if(map->height > MAX_HEIGHT) 
	// {
	// 	ft_printf_fd("Map height is too big!\n", 2);
	// 	return(false);
	// }
	// if(map->width > MAX_WIDTH) 
	// {
	// 	ft_printf_fd("Map width is too big!\n", 2);
	// 	return(false);
	// }
	if (i < 0 || i >= map->height || j < 0 || j >= map->width)
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
	is_playable = floodfill(map, is_explored, y, x);
	free_explored_grid((void **)is_explored);
	if (!is_playable)
		return (false);
	return (true);
}
