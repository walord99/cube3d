/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:07:15 by yothmani          #+#    #+#             */
/*   Updated: 2024/05/26 14:42:20 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	between_lines_check(char *current_line, int *line_counter, int *fd)
{
	while (current_line)
	{
		if (first_non_white(current_line) != -1)
			return (handle_error(ERR_NL, current_line, *fd));
		else
		{
			current_line = get_next_line(*fd, true);
			line_counter++;
		}
	}
	return (0);
}

void	finalize_map_processing(t_map *map, char *current_line, int grid_idx,
		int line_counter)
{
	int	fd;

	fd = map->fd;
	map->height = (unsigned int)line_counter - (unsigned int)grid_idx;
	map->first_map_line = grid_idx;
	free(current_line);
	current_line = NULL;
	close(fd);
}

int	full_tex_check(t_map *map, char *current_line, int *line_counter,
		int *grid_idx)
{
	int	fd;

	fd = map->fd;
	if (is_valid_tex_prefix(current_line))
	{
		if (element_parse(map, current_line, &fd))
			return (1);
	}
	else
	{
		if (process_map(map, current_line, line_counter, grid_idx))
			return (1);
	}
	return (0);
}

int	process_map(t_map *map, char *current_line, int *line_counter,
		int *grid_idx)
{
	int		fd;
	char	*new_line;

	if (is_white_space(*current_line))
		new_line = current_line;
	fd = map->fd;
	while (is_white_space(*current_line))
		current_line++;
	if (*current_line == '1')
	{
		if (verify_checked_elements(map, &fd))
		{
			free(new_line);
			return (1);
		}
		get_map_dimensions(map, current_line, grid_idx, line_counter);
	}
	else
	{
		if (process_map_line(current_line, line_counter, grid_idx, &fd))
			return (1);
	}
	return (0);
}

int	last_check(t_map *map, char *current_line, int line_counter, int grid_idx)
{
	int	fd;

	fd = map->fd;
	if (grid_idx == -1)
		return (handle_error(ERR_INC_MAP, current_line, fd));
	finalize_map_processing(map, current_line, grid_idx, line_counter);
	return (0);
}
