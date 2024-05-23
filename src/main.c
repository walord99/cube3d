/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:40:51 by joe_jam           #+#    #+#             */
/*   Updated: 2024/05/23 00:44:43 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		mlx_delete_texture(game->map.textures[i]);
		i++;
	}
	mlx_delete_image(game->mlx, game->rendered);
	mlx_delete_image(game->mlx, game->minimap.arrow);
	mlx_delete_image(game->mlx, game->minimap.circle);
	mlx_delete_image(game->mlx, game->minimap.render);
	i = 0;
	while (game->doors[i])
		free(game->doors[i++]);
	free(game->doors);
	mlx_terminate(game->mlx);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_game	game;

	fd = arg_check(argc, argv);
	if (fd < 0)
		return (1);
	init_map_struct(&game.map, fd);
	if (parse(argc, argv, &game.map, &fd))
		return (1);
	close(fd);
	if (init_game(&game))
		return (1);
	free_game(&game);
	return (0);
}
