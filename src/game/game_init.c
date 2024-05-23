/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:23:23 by bplante           #+#    #+#             */
/*   Updated: 2024/05/23 11:42:33 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_door_array(t_game *game)
{
	unsigned int	x;
	unsigned int	y;
	char			tile;
	t_list			*doors;
	t_door			*door;

	doors = NULL;
	x = 0;
	while (x++ < game->map.width)
	{
		y = 0;
		while (y < game->map.height)
		{
			tile = get_map_loc(x - 1, y++, &game->map);
			if (tile == '|' || tile == '-')
			{
				door = ft_calloc(1, sizeof(t_door));
				door->map_pos = (t_int_vector){.x = x - 1, .y = y - 1};
				door->open_track = 0;
				doors = ft_lstadd_back(doors, (void *)door);
			}
		}
	}
	game->doors = lst_to_tab(doors);
	lst_destroy_nodes(doors);
}

void	init_player_move_box(t_game *game)
{
	game->aabb_corners[0].x = -PLAYER_MOVE_BOX;
	game->aabb_corners[0].y = -PLAYER_MOVE_BOX;
	game->aabb_corners[1].x = PLAYER_MOVE_BOX;
	game->aabb_corners[1].y = -PLAYER_MOVE_BOX;
	game->aabb_corners[2].x = PLAYER_MOVE_BOX;
	game->aabb_corners[2].y = PLAYER_MOVE_BOX;
	game->aabb_corners[3].x = -PLAYER_MOVE_BOX;
	game->aabb_corners[3].y = PLAYER_MOVE_BOX;
}

int	minimap_fixed_textures(t_game *game)
{
	if (create_texture(&game->map, "includes/textures/circle.png", CIRCLE)
		|| create_texture(&game->map, "includes/textures/arrow.png", ARROW))
		return (1);
	game->minimap.arrow = mlx_texture_to_image(game->mlx,
			game->map.textures[ARROW]);
	game->minimap.circle = mlx_texture_to_image(game->mlx,
			game->map.textures[CIRCLE]);
	mlx_resize_image(game->minimap.arrow, 20, 20);
	mlx_resize_image(game->minimap.circle, SCREENHEIGHT / 4, SCREENHEIGHT / 4);
	mlx_image_to_window(game->mlx, game->minimap.arrow, SCREENWIDTH
		- SCREENHEIGHT / 4 / 2 - game->minimap.arrow->width / 2, SCREENHEIGHT
		/ 4 / 2 - game->minimap.arrow->height / 2);
	mlx_image_to_window(game->mlx, game->minimap.circle, SCREENWIDTH
		- SCREENHEIGHT / 4, 0);
	game->minimap.arrow->instances[0].z = 4;
	game->minimap.circle->instances[0].z = 5;
	return (0);
}

void	init_player_info(t_game *game)
{
	game->pos.x = game->map.spawn_x + 0.5;
	game->pos.y = game->map.spawn_y + 0.5;
	game->look_dir.x = 0;
	game->look_dir.y = -1;
	game->plane.x = 1 / (((double)1920 / (double)1080) / ((double)SCREENWIDTH
				/ (double)SCREENHEIGHT));
	game->plane.y = 0;
	if (game->map.spawn_direction == 'S')
		rotate_player(game, deg_to_rad(180));
	else if (game->map.spawn_direction == 'E')
		rotate_player(game, 90);
	else if (game->map.spawn_direction == 'W')
		rotate_player(game, -90);
	init_player_move_box(game);
}

int	init_game(t_game *game)
{
	game->rendered = NULL;
	game->minimap.render = NULL;
	init_player_info(game);
	create_door_array(game);
	game->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "cub3d", false);
	if (minimap_fixed_textures(game) || create_texture(&game->map,
			"includes/textures/door.png", DOOR))
		return (1);
	game->fc_img = create_floor_ceil_image(game);
	mlx_image_to_window(game->mlx, game->fc_img, 0, 0);
	game->fc_img->instances[0].z = 0;
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(game->mlx, &loop_hook, game);
	mlx_set_mouse_pos(game->mlx, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	mlx_loop(game->mlx);
	return (0);
}
