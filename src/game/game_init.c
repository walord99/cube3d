/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:23:23 by bplante           #+#    #+#             */
/*   Updated: 2024/05/13 16:13:50 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_door_array(t_game *game)
{
	int		x;
	int		y;
	char	tile;
	t_list	*doors;
	t_door	*door;

	doors = NULL;
	x = 0;
	while (x < game->map.width)
	{
		y = 0;
		while (y < game->map.height)
		{
			tile = get_map_coordinate(x, y, &game->map);
			if (tile == '|' || tile == '-')
			{
				door = ft_calloc(1, sizeof(t_door));
				door->map_pos = (t_int_vector){.x = x, .y = y};
				door->open_track = 0;
				doors = ft_lstadd_back(doors, (void *)door);
			}
			y++;
		}
		x++;
	}
	game->doors = lst_to_tab(doors);
	lst_destroy_nodes(doors);
}

void	fill_square(mlx_image_t *img, uint32_t color, t_int_vector start,
		t_int_vector end)
{
	int	temp;

	temp = start.y;
	while (start.x != end.x)
	{
		start.y = temp;
		while (start.y != end.y)
		{
			mlx_put_pixel(img, start.x, start.y, color);
			start.y++;
		}
		start.x++;
	}
}

mlx_image_t	*create_floor_ceil_image(t_game *game)
{
	mlx_image_t		*fc_img;
	t_int_vector	start;
	t_int_vector	end;

	fc_img = mlx_new_image(game->mlx, SCREENWIDTH, SCREENHEIGHT);
	start.x = 0;
	start.y = 0;
	end.x = SCREENWIDTH;
	end.y = SCREENHEIGHT / 2;
	fill_square(fc_img, game->map.cieling, start, end);
	start.y = SCREENHEIGHT / 2;
	start.x = 0;
	end.x = SCREENWIDTH;
	end.y = SCREENHEIGHT;
	fill_square(fc_img, game->map.floor, start, end);
	return (fc_img);
}

void	init_player_move_box(t_game *game)
{
	game->AABB_corners[0].x = -PLAYER_MOVE_BOX;
	game->AABB_corners[0].y = -PLAYER_MOVE_BOX;
	game->AABB_corners[1].x = PLAYER_MOVE_BOX;
	game->AABB_corners[1].y = -PLAYER_MOVE_BOX;
	game->AABB_corners[2].x = PLAYER_MOVE_BOX;
	game->AABB_corners[2].y = PLAYER_MOVE_BOX;
	game->AABB_corners[3].x = -PLAYER_MOVE_BOX;
	game->AABB_corners[3].y = PLAYER_MOVE_BOX;
}

void	init_game(t_game *game)
{
	// t_dbl_vector mov;
	// mov.x = 0;
	// mov.y = 0;
	game->pos.x = game->map.spawn_x + 0.5;
	game->pos.y = game->map.spawn_y + 0.5;
	game->look_dir.x = 0;
	game->look_dir.y = -1;
	game->plane.x = 1;
	game->plane.y = 0;
	game->rendered = NULL;
	game->minimap.render = NULL;
	if(game->map.spawn_direction == 'S')
		rotate_player(game, deg_to_rad(180));
	else if (game->map.spawn_direction == 'E')
		rotate_player(game, 90);
	else if (game->map.spawn_direction == 'W')
		rotate_player(game, -90);
	create_door_array(game);
	init_player_move_box(game);
	game->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "cub3d", false);
	game->fc_img = create_floor_ceil_image(game);
	mlx_image_to_window(game->mlx, game->fc_img, 0, 0);
	game->fc_img->instances[0].z = 0;
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(game->mlx, &loop_hook, game);
	mlx_set_mouse_pos(game->mlx, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	mlx_loop(game->mlx);
}
