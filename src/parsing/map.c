/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:49:31 by yothmani          #+#    #+#             */
/*   Updated: 2024/04/13 01:12:59 by yothmani         ###   ########.fr       */
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
	map->has_direction = 0;
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

bool	is_char_valid(char **str)
{
	int	has_direction;
	int	x;
	int	y;

	has_direction = 0;
	x = 0;
	while (str[x])
	{
		y = 0;
		while (str[x][y])
		{
			if (str[x][y] == '1' || str[x][y] == '0'
				|| is_white_space(str[x][y]))
				y++;
			else if (str[x][y] == 'N' || str[x][y] == 'S' || str[x][y] == 'E'
				|| str[x][y] == 'W')
			{
				has_direction++;
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
	if (has_direction != 1)
	{
		printf("Only one start point is permitted! You have %d\n",
			has_direction);
		return (false);
	}
	return (true);
}

int	first_and_last_line_check(char **str)
{
	int	start;
	int	end;
	int	x;

	start = 0;
	end = ft_strlen(str[0]);
	x = 0;
	while (is_white_space(str[x][start]))
		start++;
	while (is_white_space(str[x][end - 1]))
		end--;
	while (start < end)
	{
		if (str[x][start] != '1' && str[x][start] != ' ')
		{
			printf("first line has incorrect char [%c].\n", str[x][start]);
			return (1);
		}
		start++;
	}
	while (str[x])
		x++;
	x--;
	end = ft_strlen(str[x]);
	start = 0;
	while (is_white_space(str[x][start]))
		start++;
	while (is_white_space(str[x][end - 1]))
		end--;
	while (start < end)
	{
		if (str[x][start] != '1' && str[x][start] != ' ')
		{
			printf("last line has incorrect char [%c].\n", str[x][start]);
			return (1);
		}
		start++;
	}
	return (0);
}

int	colonne_check(char **str)
{
	int	x;
	int	y;

	if (!str)
		return (0);
	x = 0;
	while (str[x])
	{
		y = 0;
		while (is_white_space(str[x][y]))
			y++;
		if (str[x][y] != '1')
		{
			printf("col [%d] is not closed\n", x);
			return (1);
		}
		while (str[x][y])
			y++;
		y--;
		while (y >= 0 && is_white_space(str[x][y]))
			y--;
		if (str[x][y] != '1')
		{
			printf("col [%d] is not closed\n", x);
			return (1);
		}
		x++;
	}
	return (0);
}

bool	is_map_valid(char **str)
{
	if (!first_and_last_line_check(str) && !colonne_check(str)
		&& is_char_valid(str))
		return (true);
	return (false);
}

char	**allocate_grid(t_map *map)
{
	int	i;
	int	j;

	map->grid = malloc(map->height * sizeof(char *));
	if (!map->grid)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = malloc((1 + map->width) * sizeof(char));
		if (!map->grid[i])
		{
			j = 0;
			while (j < i)
			{
				free(map->grid[j]);
				j++;
			}
			free(map->grid);
			return (NULL);
		}
		i++;
	}
	return (map->grid);
}

void	set_value_to_grid(t_map *map, int width, int height, char c)
{
	if (c == '0')
		map->grid[height][width] = '0';
	else if (c == '1')
		map->grid[height][width] = '1';
	else if ((c == 'N' || c == 'E' || c == 'S' || c == 'W'))
		map->grid[height][width] = c;
	else
		map->grid[height][width] = ' ';
}


//TODO: check why the function isnt printing rhe whole grid (from first_map_line to height)
void	populate_grid(t_map *map, int fd)
{
	unsigned int	i;
	char			*current_line;
	int				width;

	if (!map || map->first_map_line == -1 || !map->grid)
		return ;
	i = 0;
	while (i < map->first_map_line - 1)
	{
		get_next_line(fd, true);
		i++;
	}
	i = map->first_map_line;
	while (i != map->height)
	{
		current_line = get_next_line(fd, true);
		width = 0;
		while (width < map->width )
		{
			if ((size_t)width < ft_strlen(current_line))
				// map->grid[i][width] = current_line[width];
				set_value_to_grid(map, width, i, current_line[width]);
			else
				set_value_to_grid(map, width, i, ' ');
			width++;
		}
		i++;
	}
}
