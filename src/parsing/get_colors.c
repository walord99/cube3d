/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:58:27 by joe_jam           #+#    #+#             */
/*   Updated: 2024/05/26 14:42:33 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_floor_color(t_map *map, char *current_line)
{
	char	*new_current_line;
	char	**split;

	new_current_line = ft_strtrim(current_line, "F");
	split = ft_split(new_current_line, ',');
	if (!split)
	{
		free(new_current_line);
		return ;
	}
	map->floor = rbga_builder(ft_atoi(split[0]), ft_atoi(split[1]),
			ft_atoi(split[2]), 255);
	free(new_current_line);
	free_tab((void **)split, &free);
}

void	get_ceiling_color(t_map *map, char *current_line)
{
	char	*new_current_line;
	char	**split;

	new_current_line = ft_strtrim(current_line, "C");
	split = ft_split(new_current_line, ',');
	if (!split)
	{
		free(new_current_line);
		return ;
	}
	map->floor = rbga_builder(ft_atoi(split[0]), ft_atoi(split[1]),
			ft_atoi(split[2]), 255);
	free(new_current_line);
	free_tab((void **)split, &free);
}

int	full_color_check(t_map *map, char *current_line, int fd, char color_pref)
{
	bool	*color_checked;
	char	*err_msg;

	color_checked = NULL;
	err_msg = NULL;
	if (color_pref == 'F')
	{
		color_checked = &map->checked_element.f_color;
		err_msg = ERR_F;
	}
	else
	{
		color_checked = &map->checked_element.c_color;
		err_msg = ERR_C;
	}
	if (*color_checked)
		return (handle_error(ERR_DUP_COLOR, current_line, fd));
	if (!is_valid_color_str(current_line))
		return (handle_error(err_msg, current_line, fd));
	if (color_pref == 'F')
		get_floor_color(map, current_line);
	else
		get_ceiling_color(map, current_line);
	*color_checked = true;
	return (0);
}
