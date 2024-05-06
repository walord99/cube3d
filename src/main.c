/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:40:51 by joe_jam           #+#    #+#             */
/*   Updated: 2024/05/06 16:43:10 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_game 	game;

	fd = arg_check(argc, argv);
	if (fd < 0)
		return (1);
	init_map_struct(&game.map);
	if(parse(argc, argv, &game.map, &fd))
		return 1;
	close(fd);
	init_game(&game);
	mlx_delete_image(game.mlx, game.rendered);
	mlx_terminate(game.mlx);
	return (0);
}
