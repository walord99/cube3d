/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 01:01:57 by joe_jam           #+#    #+#             */
/*   Updated: 2024/05/21 19:39:57 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	open_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	return (fd);
}

int	check_file_extension(char *file_name)
{
	int	i;
	int	dot_position;

	dot_position = -1;
	i = 0;
	while (file_name[i] != '\0')
	{
		if (file_name[i] == '.')
			dot_position = i;
		i++;
	}
	if (dot_position == -1 || dot_position == i - 1)
		return (1);
	if (i - dot_position != 4)
		return (1);
	if (ft_strncmp(".cub", &file_name[dot_position], 4))
		return (1);
	return (0);
}

int	full_element_check(t_map *map, char *current_line, int *line_counter,
		int *grid_idx)
{
	int		fd;
	char	color_pref;

	fd = map->fd;
	if (*current_line == 'F' || *current_line == 'C')
	{
		color_pref = *current_line;
		if (full_color_check(map, current_line, fd, color_pref))
			return (1);
	}
	else
	{
		if (full_tex_check(map, current_line, line_counter, grid_idx))
			return (1);
	}
	return (0);
}

int	handle_empty_line(char **current_line, int *line_counter, t_map *map,
		int *grid_idx)
{
	int	fd;

	fd = map->fd;
	if (*grid_idx == -1)
	{
		advance_to_next_line(current_line, line_counter, fd);
		return (0);
	}
	else
	{
		if (between_lines_check(*current_line, line_counter, &fd))
			return (1);
	}
	return (0);
}

int	read_and_parse_file(int fd, t_map *map)
{
	char	*current_line;
	int		line_counter;
	int		grid_idx;

	current_line = get_next_line(fd, true);
	if (!current_line)
		return (handle_error(ERR_EMPTY_MAP, current_line, fd));
	line_counter = 1;
	grid_idx = -1;
	while (current_line)
	{
		if (is_line_empty_or_whitespace(current_line))
		{
			if (handle_empty_line(&current_line, &line_counter, map, &grid_idx))
				return (1);
			continue ;
		}
		else
		{
			if (full_element_check(map, current_line, &line_counter, &grid_idx))
				return (1);
		}
		advance_to_next_line(&current_line, &line_counter, fd);
	}
	return (last_check(map, current_line, line_counter, grid_idx));
}
