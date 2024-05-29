/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:38:56 by yothmani          #+#    #+#             */
/*   Updated: 2024/05/26 14:40:26 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	process_map_line(char *current_line, int *line_counter, int *map_start_idx,
		int *fd)
{
	int	idx;

	idx = first_non_white(current_line);
	if (!is_valid_tex_prefix(current_line) && current_line[idx] != 'F'
		&& current_line[idx] != 'C')
	{
		if (*map_start_idx != -1 && *map_start_idx <= *line_counter)
		{
			ft_printf_fd("Column [%d] is not closed\n", 2, *map_start_idx + 1);
			return (1);
		}
		else
			return (handle_error(ERR_INV_ELEM, current_line, *fd));
	}
	else
		return (handle_error(ERR_DUP_ELEM, current_line, *fd));
	return (0);
}

bool	is_line_empty_or_whitespace(char *current_line)
{
	int	idx;

	idx = first_non_white(current_line);
	return (idx == -1);
}

char	*double_trim(char *current_line)
{
	char	*trimmed_line;
	char	*double_trimmed_line;
	char	*final_trimmed_line;
	char	*temp;

	trimmed_line = ft_strtrim(current_line, " \t");
	if (!trimmed_line)
		return (NULL);
	temp = trimmed_line;
	trimmed_line += 2;
	double_trimmed_line = ft_strtrim(trimmed_line, " \n");
	free(temp);
	if (!double_trimmed_line)
		return (NULL);
	temp = double_trimmed_line;
	double_trimmed_line += 2;
	final_trimmed_line = ft_strtrim(double_trimmed_line, " \n");
	free(temp);
	if (!final_trimmed_line)
		return (NULL);
	return (final_trimmed_line);
}

int	verify_checked_elements(t_map *map, int *fd)
{
	if (!map->checked_element.c_color || !map->checked_element.f_color)
		return (handle_error(ERR_MISSING_COLOR, NULL, *fd));
	else if (!map->checked_element.texture_ea)
	{
		map->textures[1] = NULL;
		return (handle_error(ERR_MISSING_E_ELEM, NULL, *fd));
	}
	else if (!map->checked_element.texture_we)
	{
		map->textures[3] = NULL;
		return (handle_error(ERR_MISSING_W_ELEM, NULL, *fd));
	}
	else if (!map->checked_element.texture_so)
	{
		map->textures[2] = NULL;
		return (handle_error(ERR_MISSING_S_ELEM, NULL, *fd));
	}
	else if (!map->checked_element.texture_no)
	{
		map->textures[0] = NULL;
		return (handle_error(ERR_MISSING_N_ELEM, NULL, *fd));
	}
	return (0);
}

void	get_map_dimensions(t_map *map, char *current_line, int *map_start_idx,
		int *line_counter)
{
	unsigned int	width;

	width = ft_strlen(current_line);
	if (width > map->width)
		map->width = width;
	if (*map_start_idx == -1)
		*map_start_idx = *line_counter;
}
