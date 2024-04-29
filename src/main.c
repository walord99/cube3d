/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:40:51 by joe_jam           #+#    #+#             */
/*   Updated: 2024/04/29 17:30:47 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_map	*map;
	int		i;

	fd = arg_check(argc, argv);
	if (fd < 0)
		return (1);
	map = init_map_struct();
	if (!map)
	{
		free_map(map);
		close(fd);
		return (1);
	}
	parse(argc, argv, map, &fd);
	close(fd);
	return (0);
}
