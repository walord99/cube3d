/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:49:31 by yothmani          #+#    #+#             */
/*   Updated: 2024/04/18 19:18:30 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_white_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

/* Returns -1 if line is empty
	else return the index of the first non white character*/
int	first_non_white(char *line)
{
	int	i;
	int	line_len;

	i = 0;
	line_len = (int)ft_strlen(line);
	while (line[i] && is_white_space(line[i]))
		i++;
	if (i == line_len)
		return (-1);
	return (i);
}

t_map	*init_map_struct(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->grid = NULL;
	map->height = 0;
	map->width = 0;
	map->first_map_line = -1;
	map->has_direction = false;
	map->checked_element = (t_element_check){
		.f_color = false,
		.c_color = false,
		.texture_no = false,
		.texture_so = false,
		.texture_we = false,
		.texture_ea = false,
	};
	return (map);
}

bool	is_char_valid(char **str, t_map map)
{
	int	x;
	int	y;
	int	len;

	x = 0;
	while (x < map.height)
	{
		// str[x] = ft_strtrim(str[x], "\n");
		y = 0;
		len = (int)ft_strlen(str[x]);
		// printf("length: ==>%i\n", len);
		// printf("line %i: ----->%s\n", x, str[x]);
		// if(len > map.width)
		// {
		// 	printf("error\n");
		// 	return(false);
		// }
		while (y < map.width)
		{
			if (str[x][y] == '1' || str[x][y] == '0'
				|| is_white_space(str[x][y]))
				y++;
			else if (str[x][y] == 'N' || str[x][y] == 'S' || str[x][y] == 'E'
				|| str[x][y] == 'W')
			{
				if (map.has_direction)
				{
					printf("Only one start point is permitted\n");
					return (false);
				}
				map.has_direction++;
				y++;
			}
			else
			{
				printf("Invalid character [%c] was found in line [%d]\n",
					str[x][y], x);
				return (false);
			}
		}
		x++;
	}
	return (true);
}

int	first_and_last_line_check(char **str, t_map map)
{
	if (!str)
		return (0);
	int start, end, x;
	start = 0;
	end = map.width;
	x = 0;
	while (is_white_space(str[x][start]))
		start++;
	while (is_white_space(str[x][end - 1]))
		end--;
	while (start < end)
	{
		if (str[x][start] != '1' && str[x][start] != ' ')
		{
			printf("First line has incorrect character [%c].\n", str[x][start]);
			return (1);
		}
		start++;
	}
	x = map.height - 1;
	start = 0;
	while (is_white_space(str[x][start]))
		start++;
	end = map.width;
	while (is_white_space(str[x][end - 1]))
		end--;
	while (start < end)
	{
		if (str[x][start] != '1' && str[x][start] != ' ')
		{
			printf("Last line has incorrect character [%c].\n", str[x][start]);
			return (1);
		}
		start++;
	}
	return (0);
}

int	colonne_check(char **str, t_map map)
{
	int	x;
	int	y;
	int	end;

	if (!str)
		return (0);
	x = 0;
	while (x < map.height)
	{
		y = 0;
		while (is_white_space(str[x][y]))
			y++;
		if (str[x][y] != '1')
		{
			if (first_non_white(str[x]) != -1)
			{
				printf("Column [%d] is not closed\n", x);
				return (1);
			}
		}
		end = map.width;
		while (end > 0 && is_white_space(str[x][end - 1]))
			end--;
		if (str[x][end - 1] != '1')
		{
			if (first_non_white(str[x]) != -1)
			{
				printf("Column [%d] is not closed\n", x);
				return (1);
			}
		}
		x++;
	}
	return (0);
}

bool	is_map_valid(char **str, t_map map)
{
	if (!is_char_valid(str, map))
		return (false);
	if (colonne_check(str, map))
	{
		printf("col check\n");
		return (false);
	}
	if (first_and_last_line_check(str, map))
	{
		printf("first last\n");
		return (false);
	}
	return (true);
}

void	allocate_grid(t_map *map)
{
	int	i;

	map->grid = malloc(map->height * sizeof(char *));
	if (!map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = malloc((map->width + 1) * sizeof(char));
		i++;
	}
	return ;
}

void	set_value_to_grid(t_map *map, int width, int height, char c)
{
	// if ((c == 'N' || c == 'E' || c == 'S' || c == 'W') || c == '1'
	// || c== '0')
	// 	map->grid[height][width] = c;
	// else
	// 	map->grid[height][width] = ' ';
	map->grid[height][width] = c;
}

// TODO: check why the function isnt printing rhe whole grid (from first_map_line to height)
void	populate_grid(t_map *map, int fd)
{
	int		i;
	char	*current_line;
	int		width;

	if (!map || map->first_map_line == -1 || !map->grid)
		return ;
	i = 0;
	while (i < map->first_map_line - 1)
	{
		get_next_line(fd, true);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		current_line = get_next_line(fd, true);
		width = 0;
		while (width < map->width)
		{
			if ((size_t)width < ft_strlen(current_line))
				set_value_to_grid(map, width, i, current_line[width]);
			else
				set_value_to_grid(map, width, i, ' ');
			width++;
		}
		free(current_line);
		i++;
	}
	current_line = NULL;
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map)
	{
		if (map->grid)
		{
			while (i < map->height)
			{
				free(map->grid[i]);
				i++;
			}
			free(map->grid);
		}
		free(map);
	}
	map->grid = NULL;
	map = NULL;
}
