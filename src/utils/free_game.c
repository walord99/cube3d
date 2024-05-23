/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:58:34 by yothmani          #+#    #+#             */
/*   Updated: 2024/05/23 15:17:32 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_images(t_game *game)
{
	if (game->rendered)
		mlx_delete_image(game->mlx, game->rendered);
	if (game->minimap.arrow)
		mlx_delete_image(game->mlx, game->minimap.arrow);
	if (game->minimap.circle)
		mlx_delete_image(game->mlx, game->minimap.circle);
	if (game->minimap.render)
		mlx_delete_image(game->mlx, game->minimap.render);
}

void	free_textures(t_game game)
{
	int	i;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		if (game.map.textures[i])
			mlx_delete_texture(game.map.textures[i]);
		i++;
	}
}

void	free_doors(t_game *game)
{
	int	i;

	i = 0;
	while (game->doors[i])
		free(game->doors[i++]);
	free(game->doors);
}

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		mlx_delete_texture(game->map.textures[i]);
		i++;
	}
	free_images(game);
	free_doors(game);
	free_map(&game->map);
	mlx_terminate(game->mlx);
}
