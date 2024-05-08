/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:30:24 by yothmani          #+#    #+#             */
/*   Updated: 2024/05/07 13:55:21 by joe_jam          ###   ########.fr       */
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

int	arg_check(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		printf(ERR_ARGC);
		return (-2);
	}
	if (check_file_extension(argv[1]))
	{
		ft_printf_fd(ERR_BADFILE, 2);
		return (-1);
	}
	fd = open_file(argv[1]);
	return (fd);
}

int	grid_parse(t_map *map)
{
	if (!is_map_valid(map->grid, map))
	{
		free_map(map);
		return (1);
	}
	if (!is_map_playable(map))
	{
		ft_printf_fd(ERR_FLOOD, 2);
		free_map(map);
		return (1);
	}
	return (0);
}

int	parse(int argc, char **argv, t_map *map, int *fd)
{
	if (file_check(argc, argv, fd, map))
		return (1);
	allocate_grid(map);
	populate_grid(map, *fd);
	if (grid_parse(map))
		return (1);
	return (0);
}
