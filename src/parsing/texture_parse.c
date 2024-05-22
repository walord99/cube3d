/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:46:17 by yothmani          #+#    #+#             */
/*   Updated: 2024/05/21 18:22:30 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_valid_tex_prefix(char *tex_str)
{
	char	*tex_pref;
	bool	result;

	tex_pref = ft_strtrim(tex_str, " \t");
	if (!tex_pref)
		return (false);
	result = ((tex_pref[0] == 'N' && tex_pref[1] == 'O') || (tex_pref[0] == 'S'
				&& tex_pref[1] == 'O') || (tex_pref[0] == 'W'
				&& tex_pref[1] == 'E') || (tex_pref[0] == 'E'
				&& tex_pref[1] == 'A')) && (tex_pref[2] == ' ');
	free(tex_pref);
	return (result);
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

int	load_texture(t_map *map, char *path_to_tex, int direction)
{
	map->textures[direction] = mlx_load_png(path_to_tex);
	if (!map->textures[direction])
		return (1);
	return (0);
}

int	create_texture(t_map *map, char *path_to_tex, int direction)
{
	if (load_texture(map, path_to_tex, direction))
	{
		ft_printf_fd("BAD PATH\n", 2);
		return (1);
	}
	return (0);
}

bool	is_valid_tex(char *path_to_tex)
{
	if (check_tex_extension(path_to_tex))
		return (false);
	return (true);
}
