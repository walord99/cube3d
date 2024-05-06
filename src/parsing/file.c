/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 01:01:57 by joe_jam           #+#    #+#             */
/*   Updated: 2024/05/06 11:45:55 by yothmani         ###   ########.fr       */
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

int	arg_check(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		printf(ERR_ARGC);
		return (-1);
	}
	if (check_file_extension(argv[1]))
	{
		ft_printf_fd(ERR_BADFILE, 2);
		return (-1);
	}
	fd = open_file(argv[1]);
	return (fd);
}

int	handle_error(char *error_msg, char *current_line, int fd)
{
	ft_printf_fd("%s\n", 2, error_msg);
	free(current_line);
	close(fd);
	return (1);
}

// TODO:put in norm this function

int	read_and_parse_file(int fd, t_map *map)
{
	char			*current_line;
	int				line_counter;
	int				map_start_idx;
	// int				idx = 0;

	current_line = get_next_line(fd, true);
	if (!current_line)
		return (handle_error(ERR_EMPTY_MAP, current_line, fd));
	line_counter = 1;
	map_start_idx = -1;
	while (current_line)
	{
		if (is_line_empty_or_whitespace(current_line))
		{
			if (map_start_idx == -1)
			{
				current_line = get_next_line(fd, true);
				line_counter++;
				continue ;
			}
			else
			{
				while (current_line)
				{
					if (first_non_white(current_line) != -1)
						return (handle_error(ERR_NL, current_line, fd));
					else
					{
						current_line = get_next_line(fd, true);
						line_counter++;
					}
				}
			}
		}
		else
		{
			if (*current_line == 'F' && !map->checked_element.f_color)
			{
				if (!is_valid_color_str(current_line))
					return (handle_error(ERR_F, current_line, fd));
				else
					map->checked_element.f_color = true;
			}
			else if (*current_line == 'C' && !map->checked_element.c_color)
			{
				if (!is_valid_color_str(current_line))
					return (handle_error(ERR_C, current_line, fd));
				else
					map->checked_element.c_color = true;
			}
			else if (is_valid_tex_prefix(current_line))
			{
				if (element_parse(map, current_line, &fd))
					return (1);
			}
			else
			{
				if (*current_line == '1')
				{
					if (verify_checked_elements(map, current_line, &fd))
						return (1);
					else
						get_map_dimensions(map, current_line, &map_start_idx,
							&line_counter);
				}
				else
				{
					if (process_map_line(current_line, &line_counter,
							&map_start_idx, &fd))
						return (1);
				}
			}
		}
		current_line = get_next_line(fd, true);
		line_counter++;
	}
	if (map_start_idx == -1)
		return (handle_error(ERR_INC_MAP, current_line, fd));
	map->height = (unsigned int)line_counter - (unsigned int)map_start_idx;
	map->first_map_line = map_start_idx;
	free(current_line);
	current_line = NULL;
	close(fd);
	return (0);
}
