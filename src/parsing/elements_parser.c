/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:55:00 by yothmani          #+#    #+#             */
/*   Updated: 2024/05/06 16:45:11 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*double_trim(char *current_line)
{
	current_line = ft_strtrim(current_line, " \t");
	current_line = current_line + 2;
	current_line = ft_strtrim(current_line, " \n");
	current_line = ft_strtrim(current_line, " \t");
	current_line = current_line + 2;
	current_line = ft_strtrim(current_line, " \n");
	current_line = ft_strtrim(current_line, " \t");
	current_line = current_line + 2;
	current_line = ft_strtrim(current_line, " \n");
	current_line = ft_strtrim(current_line, " \t");
	current_line = current_line + 2;
	current_line = ft_strtrim(current_line, " \n");
	return (current_line);
}


//TODO:organize this function
int	element_parse(t_map *map, char *current_line, int *fd)
{
	if (*current_line == 'N' && !map->checked_element.texture_no)
	{
		char *new = ft_strtrim(current_line, " \n");
		if(create_texture(map, new + 3))
			return (handle_error(ERR_TEX_N, current_line, *fd));
		free(new);
		char *new_current_line = double_trim(current_line);
		if (!is_valid_tex(map, current_line))
			return (handle_error(ERR_TEX_N, current_line, *fd));
		else
			map->checked_element.texture_no = true;
	}
	else if (*current_line == 'S' && !map->checked_element.texture_so)
	{
		char *new = ft_strtrim(current_line, " \n");
		if(create_texture(map, new + 3))
			return (handle_error(ERR_TEX_S, current_line, *fd));
		free(new);
		char *new_current_line = double_trim(current_line);
		if (is_valid_tex(map, current_line))
			map->checked_element.texture_so = true;
		else
			return (handle_error(ERR_TEX_S, current_line, *fd));
	}
	else if (*current_line == 'E' && !map->checked_element.texture_ea)
	{
		char *new = ft_strtrim(current_line, " \n");
		if(create_texture(map, new + 3))
			return (handle_error(ERR_TEX_E, current_line, *fd));
		free(new);
		char *new_current_line = double_trim(current_line);
		if (is_valid_tex(map, current_line))
			map->checked_element.texture_ea = true;
		else
			return (handle_error(ERR_TEX_E, current_line, *fd));
	}
	else if (*current_line == 'W' && !map->checked_element.texture_we)
	{
		char *new = ft_strtrim(current_line, " \n");
		if(create_texture(map, new + 3))
			return (handle_error(ERR_TEX_W, current_line, *fd));
		free(new);
		char *new_current_line = double_trim(current_line);
		if (is_valid_tex(map, current_line))
			map->checked_element.texture_we = true;
		else
			return (handle_error(ERR_TEX_W, current_line, *fd));
	}
	return (0);
}

int	verify_checked_elements(t_map *map, char *current_line, int *fd)
{
	if (!map->checked_element.c_color || !map->checked_element.f_color
		|| !map->checked_element.texture_ea || !map->checked_element.texture_we
		|| !map->checked_element.texture_so || !map->checked_element.texture_no)
		return (handle_error(ERR_INV_ELEM, current_line, *fd));
	return (0);
}

void	get_map_dimensions(t_map *map, char *current_line, int *map_start_idx,
		int *line_counter)
{
	int	width;

	width = ft_strlen(current_line);
	if (width > map->width)
		map->width = width;
	if (*map_start_idx == -1)
		*map_start_idx = *line_counter;
}
