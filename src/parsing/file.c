/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 01:01:57 by joe_jam           #+#    #+#             */
/*   Updated: 2024/04/13 01:19:20 by yothmani         ###   ########.fr       */
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
		return (1);
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

bool	is_valid_tex_prefix(char *tex_pref)
{
	if ((tex_pref[0] == 'N' && tex_pref[1] == 'O') || (tex_pref[0] == 'S'
			&& tex_pref[1] == 'O') || (tex_pref[0] == 'W' && tex_pref[1] == 'E')
		|| (tex_pref[0] == 'E' && tex_pref[1] == 'A'))
		return (tex_pref[2] == ' ');
	return (false);
}

bool is_valid_color_char(char c)
{
	if(ft_isdigit(c) || c ==',' || c ==' ')
		return true;
	else
		return false;
}

bool	is_valid_color_str(char *color_pref)
{
	bool	res;
	int		i;
	int		comma_count;

	res = false;
	comma_count = 0;
	if (color_pref[0] == 'F' || color_pref[0] == 'C')
		res = true;
	i = 2;
	while (i < (int) ft_strlen(&color_pref[1]))
	{
		if (!is_valid_color_char(color_pref[i]))
			return (false);
		if (color_pref[i] == ',')
			comma_count++;
		i++;
	}
	if (comma_count != 2)
		return (false);
	return (res);
}



int	read_and_parse_file(int fd, t_map *map)
{
	char	*current_line;
	int		line_counter;
	int		map_1st_line_idx;
	int		idx;
	unsigned int		width;

	current_line = get_next_line(fd, true);
	line_counter = 1;
	map_1st_line_idx = -1;
	while (current_line)
	{
		idx = first_non_white(current_line);
		if (idx == -1)
		{
			if(map_1st_line_idx == -1)
			{
				current_line = get_next_line(fd, true);
				line_counter++;
			}
			else
			{
				while(current_line)
				{
					if(first_non_white(current_line) != -1)
					{
						printf("Error: Empty line between map lines!\n");
						free(current_line);
						close(fd);
						return -1;
					}
					else
					{
						current_line = get_next_line(fd, true);
						line_counter++;
					}
				}
				break;
			}
		}
		else
		{
			if (current_line[idx] == 'F' && !map->checked_element.f_color)
			{
				if (!is_valid_color_str(current_line))
				{
					free(current_line);
					close(fd);
					return (-1);
				}
				else
				{
					map->checked_element.f_color = true;
				}
			}
			else if (current_line[idx] == 'C' && !map->checked_element.c_color)
			{
				if (!is_valid_color_str(current_line))
				{
					free(current_line);
					close(fd);
					return (-1);
				}
				else
					map->checked_element.c_color = true;
			}
			else if (is_valid_tex_prefix(current_line))
			{
				if (current_line[idx] == 'N'
					&& !map->checked_element.texture_no)
					map->checked_element.texture_no = true;
				else if (current_line[idx] == 'S'
					&& !map->checked_element.texture_so)
					map->checked_element.texture_so = true;
				else if (current_line[idx] == 'E'
					&& !map->checked_element.texture_ea)
					map->checked_element.texture_ea = true;
				else if (current_line[idx] == 'W'
					&& !map->checked_element.texture_we)
					map->checked_element.texture_we = true;
				else
				{
					printf("Error, double texture found!\n");
					free(current_line);
					close(fd);
					return (-1);
				}
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
					{
						printf("Error: Incomplete elements!\n");
						free(current_line);
						close(fd);
						return (-1);
					}
					else
					{
						width = ft_strlen(current_line);
						if(width > map->width)
							map->width = width;
						if(map_1st_line_idx == -1)
							map_1st_line_idx = line_counter;
					}
				}
				else
				{
					printf("Error: Map is not closed\n");
					free(current_line);
					close(fd);
					return (-1);
				}
			}
		}
		current_line = get_next_line(fd, true);
		line_counter++;
	}
	if (map_1st_line_idx == -1)
	{
		free(current_line);
		printf("Error: Incorrect Map\n");
		close(fd);
		return (-1);
	}
	map->height = (unsigned int)line_counter - (unsigned int)map_1st_line_idx;
	map->first_map_line = map_1st_line_idx;
	free(current_line);
	close(fd);
	return (map_1st_line_idx);
}
