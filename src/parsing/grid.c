/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:44:23 by yothmani          #+#    #+#             */
/*   Updated: 2024/05/21 19:40:29 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	allocate_grid(t_map *map)
{
	unsigned int	i;

	map->grid = ft_calloc(map->height, sizeof(char *));
	if (!map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = ft_calloc((map->width + 1), sizeof(char));
		i++;
	}
	return ;
}

void	set_value_to_grid(t_map *map, int width, int height, char c)
{
	map->grid[height][width] = c;
}

void	read_lines_until(int fd, int target_line)
{
	int		i;
	char	*line;

	i = 0;
	while (i < target_line)
	{
		line = get_next_line(fd, true);
		i++;
		free(line);
	}
}

void	fill_grid(t_map *map, int fd)
{
	unsigned int	i;
	char			*current_line;
	unsigned int	width;

	i = 0;
	while (i < map->height)
	{
		current_line = get_next_line(fd, true);
		width = 0;
		while (width < map->width)
		{
			if ((size_t)width < ft_strlen(current_line))
				set_value_to_grid(map, width, i, current_line[width]);
			else
				set_value_to_grid(map, width, i, ' ');
			width++;
		}
		free(current_line);
		i++;
	}
}

void	populate_grid(t_map *map, int fd)
{
	if (!map || map->first_map_line == -1 || !map->grid)
		return ;
	read_lines_until(fd, map->first_map_line - 1);
	fill_grid(map, fd);
}
