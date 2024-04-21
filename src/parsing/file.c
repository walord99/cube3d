/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 01:01:57 by joe_jam           #+#    #+#             */
/*   Updated: 2024/04/20 22:16:08 by joe_jam          ###   ########.fr       */
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

int	file_check(char **argv)
{
	int	fd;

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
	printf("%s\n", error_msg);
	free(current_line);
	close(fd);
	return (1);
}

int	read_and_parse_file(int fd, t_map *map)
{
	char			*current_line;
	int				line_counter;
	int				map_1st_line_idx;
	int				idx;
	unsigned int	width;

	current_line = get_next_line(fd, true);
	line_counter = 1;
	map_1st_line_idx = -1;
	while (current_line)
	{
		idx = first_non_white(current_line);
		if (idx == -1)
		{
			if (map_1st_line_idx == -1)
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
				break ;
			}
		}
		else
		{
			if (current_line[idx] == 'F' && !map->checked_element.f_color)
			{
				if (!is_valid_color_str(current_line))
					return (handle_error(ERR_F, current_line, fd));
				else
					map->checked_element.f_color = true;
			}
			else if (current_line[idx] == 'C' && !map->checked_element.c_color)
			{
				if (!is_valid_color_str(current_line))
					return (handle_error(ERR_C, current_line, fd));
				else
					map->checked_element.c_color = true;
			}
			else if (is_valid_tex_prefix(current_line))
			{
				if (current_line[idx] == 'N'
					&& !map->checked_element.texture_no)
				{
					current_line = ft_strtrim(current_line, " \t");
					current_line = current_line + 2;
					current_line = ft_strtrim(current_line, " \n");
					if (!is_valid_tex(current_line))
						return (handle_error(ERR_TEX_N, current_line, fd));
					else
						map->checked_element.texture_no = true;
				}
				else if (current_line[idx] == 'S'
					&& !map->checked_element.texture_so)
				{
					current_line = ft_strtrim(current_line, " \t");
					current_line = current_line + 2;
					current_line = ft_strtrim(current_line, " \n");
					if (is_valid_tex(current_line))
						map->checked_element.texture_so = true;
					else
						return (handle_error(ERR_TEX_S, current_line, fd));
				}
				else if (current_line[idx] == 'E'
					&& !map->checked_element.texture_ea)
				{
					current_line = ft_strtrim(current_line, " \t");
					current_line = current_line + 2;
					current_line = ft_strtrim(current_line, " \n");
					if (is_valid_tex(current_line))
						map->checked_element.texture_ea = true;
					else
						return (handle_error(ERR_TEX_E, current_line, fd));
				}
				else if (current_line[idx] == 'W'
					&& !map->checked_element.texture_we)
				{
					current_line = ft_strtrim(current_line, " \t");
					current_line = current_line + 2;
					current_line = ft_strtrim(current_line, " \n");
					if (is_valid_tex(current_line))
						map->checked_element.texture_we = true;
					else
						return (handle_error(ERR_TEX_W, current_line, fd));
				}
				else
					return (handle_error(ERR_DUP_TEX, current_line, fd));
			}
			else
			{
				if (current_line[idx] == '1')
				{
					if (!map->checked_element.c_color
						|| !map->checked_element.f_color
						|| !map->checked_element.texture_ea
						|| !map->checked_element.texture_we
						|| !map->checked_element.texture_so
						|| !map->checked_element.texture_no)
						return (handle_error(ERR_INC_ELEM, current_line, fd));
					else
					{
						width = ft_strlen(current_line);
						if (width > map->width)
							map->width = width;
						if (map_1st_line_idx == -1)
							map_1st_line_idx = line_counter;
					}
				}
				else
				{
					if (!is_valid_tex_prefix(current_line))
						return (handle_error(ERR_ELEM, current_line, fd));
					else
						return (handle_error(ERR_MAP_NOT_CLOSED, current_line,
								fd));
				}
			}
		}
		current_line = get_next_line(fd, true);
		line_counter++;
	}
	if (map_1st_line_idx == -1)
		return (handle_error(ERR_INC_MAP, current_line, fd));
	map->height = (unsigned int)line_counter - (unsigned int)map_1st_line_idx;
	map->first_map_line = map_1st_line_idx;
	free(current_line);
	current_line = NULL;
	close(fd);
	return (0);
}
