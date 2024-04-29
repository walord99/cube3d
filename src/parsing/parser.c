/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:30:24 by yothmani          #+#    #+#             */
/*   Updated: 2024/04/29 17:30:56 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	file_check(int argc, char **argv, int *fd, t_map *map)
{
	if (read_and_parse_file(*fd, map))
	{
		free_map(map);
		close(*fd);
		return (1);
	}
	*fd = arg_check(argc, argv);
	if (*fd == -1)
	{
		free_map(map);
		close(*fd);
		return (1);
	}
	return (0);
}

void	grid_parse(t_map *map)
{
	if (!is_map_valid(map->grid, map))
	{
		free_map(map);
		return ;
	}
	if (!is_map_playable(map))
	{
		printf("not playable\n");
		free_map(map);
		return ;
	}
}

void	parse(int argc, char **argv, t_map *map, int *fd)
{
	if (file_check(argc, argv, fd, map))
		return ;
	allocate_grid(map);
	populate_grid(map, *fd);
	grid_parse(map);
}
