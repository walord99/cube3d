/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:40:51 by joe_jam           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/23 12:53:39 by yothmani         ###   ########.fr       */
=======
/*   Updated: 2024/05/24 13:53:21 by bplante          ###   ########.fr       */
>>>>>>> parsing
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_game	game;

	fd = arg_check(argc, argv);
	if (fd < 0)
		return (1);
	init_map_struct(&game.map, fd);
<<<<<<< HEAD
	if (parse(argc, argv, &game.map, &fd))
=======
	if (parse(argc, argv, &game, &fd))
	{
		free(game.map.textures);
>>>>>>> parsing
		return (1);
	close(fd);
	if (init_game(&game))
		return (1);
	free_game(&game);
	return (0);
}
