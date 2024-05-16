/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:55:00 by yothmani          #+#    #+#             */
/*   Updated: 2024/05/16 09:02:54 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	north_texture_process(t_map *map, char *current_line, int *fd)
{
	char	*trimmed;
	char	*new_current_line;

	trimmed = ft_strtrim(current_line, " \n");
	new_current_line = double_trim(current_line);
	if (create_texture(map, trimmed + 3, NO))
	{
		free(trimmed);
		free(new_current_line);
		return (handle_error(ERR_TEX_N, current_line, *fd));
	}
	if (!is_valid_tex(map, new_current_line))
	{
		free(trimmed);
		free(new_current_line);
		return (handle_error(ERR_TEX_N, current_line, *fd));
	}
	else
		map->checked_element.texture_no = true;
	free(trimmed);
	free(new_current_line);
	return (0);
}

int	south_texture_process(t_map *map, char *current_line, int *fd)
{
	char	*trimmed;
	char	*new_current_line;

	trimmed = ft_strtrim(current_line, " \n");
	new_current_line = double_trim(current_line);
	if (create_texture(map, trimmed + 3, SO))
	{
		free(new_current_line);
		free(trimmed);
		return (handle_error(ERR_TEX_S, current_line, *fd));
	}
	free(trimmed);
	if (is_valid_tex(map, new_current_line))
		map->checked_element.texture_so = true;
	else
	{
		free(new_current_line);
		return (handle_error(ERR_TEX_S, current_line, *fd));
	}
	free(new_current_line);
	return (0);
}

int	east_texture_process(t_map *map, char *current_line, int *fd)
{
	char	*trimmed;
	char	*new_current_line;

	trimmed = ft_strtrim(current_line, " \n");
	new_current_line = double_trim(current_line);
	if (create_texture(map, trimmed + 3, EA))
	{
		free(trimmed);
		free(new_current_line);
		return (handle_error(ERR_TEX_E, current_line, *fd));
	}
	free(trimmed);
	if (is_valid_tex(map, new_current_line))
		map->checked_element.texture_ea = true;
	else
	{
		free(new_current_line);
		return (handle_error(ERR_TEX_E, current_line, *fd));
	}
	free(new_current_line);
	return (0);
}

int	west_texture_process(t_map *map, char *current_line, int *fd)
{
	char	*trimmed;
	char	*new_current_line;

	trimmed = ft_strtrim(current_line, " \n");
	new_current_line = double_trim(current_line);
	if (create_texture(map, trimmed + 3, WE))
	{
		free(trimmed);
		free(new_current_line);
		return (handle_error(ERR_TEX_W, current_line, *fd));
	}
	free(trimmed);
	if (is_valid_tex(map, new_current_line))
		map->checked_element.texture_we = true;
	else
	{
		free(new_current_line);
		return (handle_error(ERR_TEX_W, current_line, *fd));
	}
	free(new_current_line);
	return (0);
}

int	element_parse(t_map *map, char *current_line, int *fd)
{
	if (*current_line == 'N' && !map->checked_element.texture_no)
	{
		if (north_texture_process(map, current_line, fd))
			return (1);
	}
	else if (*current_line == 'S' && !map->checked_element.texture_so)
	{
		if (south_texture_process(map, current_line, fd))
			return (1);
	}
	else if (*current_line == 'E' && !map->checked_element.texture_ea)
	{
		if (east_texture_process(map, current_line, fd))
			return (1);
	}
	else if (*current_line == 'W' && !map->checked_element.texture_we)
	{
		if (west_texture_process(map, current_line, fd))
			return (1);
	}
	return (0);
}
