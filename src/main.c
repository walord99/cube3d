/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:40:51 by joe_jam           #+#    #+#             */
/*   Updated: 2024/04/13 01:19:35 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_map	*map;
	int		i;

	if (argc != 2)
	{
		printf(ERR_ARGC);
		return (1);
	}
	fd = file_check(argv);
	if (fd != -1)
	{
		map = init_map_struct();
		if (!map)
		{
			close(fd);
			return (1);
		}
		read_and_parse_file(fd, map);
		// close(fd);
		fd = file_check(argv);
		if (fd == -1)
			return (1);
		allocate_grid(map);
		populate_grid(map, fd);
		close(fd);
		if (is_map_valid(map->grid))
			printf("OK\n");
		else
			printf("KO\n");
		for (i = 0; i < map->height; i++)
		{
			printf("%s\n", map->grid[i]);
		}
		return (0);
	}
}
