/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:55:00 by yothmani          #+#    #+#             */
/*   Updated: 2024/05/26 14:48:04 by yothmani         ###   ########.fr       */
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
	if (!is_valid_tex(new_current_line))
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
	if (is_valid_tex(new_current_line))
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
	if (is_valid_tex(new_current_line))
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
	if (is_valid_tex(new_current_line))
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
	if (*current_line == 'N')
	{
		if (map->checked_element.texture_no)
			return (handle_error(ERR_DUP_ELEM, current_line, *fd));
		return (north_texture_process(map, current_line, fd));
	}
	if (*current_line == 'S')
	{
		if (map->checked_element.texture_so)
			return (handle_error(ERR_DUP_ELEM, current_line, *fd));
		return (south_texture_process(map, current_line, fd));
	}
	if (*current_line == 'E')
	{
		if (map->checked_element.texture_ea)
			return (handle_error(ERR_DUP_ELEM, current_line, *fd));
		return (east_texture_process(map, current_line, fd));
	}
	if (*current_line == 'W')
	{
		if (map->checked_element.texture_we)
			return (handle_error(ERR_DUP_ELEM, current_line, *fd));
		return (west_texture_process(map, current_line, fd));
	}
	return (0);
}
