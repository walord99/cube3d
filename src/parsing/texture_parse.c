/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:46:17 by yothmani          #+#    #+#             */
/*   Updated: 2024/04/25 16:29:36 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_valid_tex_prefix(char *tex_str)
{
	char	*tex_pref;

	tex_pref = ft_strtrim(tex_str, " \t");
	if ((tex_pref[0] == 'N' && tex_pref[1] == 'O') || (tex_pref[0] == 'S'
			&& tex_pref[1] == 'O') || (tex_pref[0] == 'W' && tex_pref[1] == 'E')
		|| (tex_pref[0] == 'E' && tex_pref[1] == 'A'))
		return (tex_pref[2] == ' ');
	return (false);
}

int	check_tex_extension(char *path_to_tex)
{
	int	i;
	int	dot_position;

	dot_position = -1;
	i = 0;
	while (path_to_tex[i] != '\0')
	{
		if (path_to_tex[i] == '.')
			dot_position = i;
		i++;
	}
	if (dot_position == -1 || dot_position == i - 1)
		return (1);
	if (i - dot_position != 4)
		return (1);
	if (ft_strncmp(".png", &path_to_tex[dot_position], 4))
		return (1);
	return (0);
}

int	load_texture(t_map *map, char *path_to_tex)
{
	map->textures->texture_test = mlx_load_png(path_to_tex);
	if (!map->textures->texture_test)
	{
		printf("HERE\n");
		return (1);
	}
	return (0);
}
void tex_to_img(t_map *map)
{
	map->textures->img_test = mlx_texture_to_image(map->mlx, map->textures->texture_test);
}

void resize_img(t_map *map)
{
	mlx_resize_image(map->textures->img_test, 50, 50);
}

int create_texture(t_map *map, char*path_to_tex)
{
	map->mlx = mlx_init(100,100,"cub3d", false);
	if(!map->mlx)
		return 1;
	if (load_texture(map, path_to_tex))
		return (1);
	tex_to_img(map);
	resize_img(map);
	return(0);
}

bool	is_valid_tex(t_map *map, char *path_to_tex)
{
	if(create_texture(map, path_to_tex)) //TODO:SEGFAULT HERE
		return(false);
	// if (load_texture(path_to_tex))
	// 	return (false);
	if (check_tex_extension(path_to_tex))
		return (false);
	return (true);
}
