/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:41:42 by yothmani          #+#    #+#             */
/*   Updated: 2024/05/21 15:19:22 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	validate_grid_characters(char **str, t_map *map)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	while (x < map->height)
	{
		y = 0;
		while (y < map->width)
		{
			if (str[x][y] == '1' || str[x][y] == '0' || str[x][y] == '|'
				|| str[x][y] == '-' || is_white_space(str[x][y]))
				y++;
			else if (str[x][y] == 'N' || str[x][y] == 'S' || str[x][y] == 'E'
				|| str[x][y] == 'W')
				y++;
			else
			{
				ft_printf_fd("Invalid character [%c] was found in line [%d]\n",
					2, str[x][y], x);
				return (false);
			}
		}
		x++;
	}
	return (true);
}

bool	handle_start_points(char **str, t_map *map)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	while (x < map->height)
	{
		y = 0;
		while (y < map->width)
		{
			if (str[x][y] == 'N' || str[x][y] == 'S' || str[x][y] == 'E'
				|| str[x][y] == 'W')
			{
				if (map->has_direction)
					return (print_and_return(ERR_SP, false));
				map->has_direction = true;
				map->spawn_direction = str[x][y];
				map->spawn_x = y;
				map->spawn_y = x;
			}
			y++;
		}
		x++;
	}
	return (true);
}

int	check_col_start(char **str, int x, int y)
{
	if (str[x][y] != '1')
	{
		if (first_non_white(str[x]) != -1)
		{
			ft_printf_fd("Column [%d] is not closed\n", 2, x);
			return (1);
		}
	}
	return (0);
}

int	check_col_end(char **str, int x, int end)
{
	if (str[x][end - 1] != '1')
	{
		if (first_non_white(str[x]) != -1)
		{
			ft_printf_fd("Column [%d] is not closed\n", 2, x);
			return (1);
		}
	}
	return (0);
}

int	check_first_and_last_line(char **str, t_map map)
{
	int	x;
	int	start;
	int	end;

	x = 0;
	start = find_first_non_whitespace(str[x]);
	end = find_last_non_whitespace(str[x], map.width);
	while (start <= end)
	{
		if (str[x][start] != '1' && str[x][start] != ' ')
			return (print_and_return(ERR_FL, 1));
		start++;
	}
	x = map.height - 1;
	start = find_first_non_whitespace(str[x]);
	end = find_last_non_whitespace(str[x], map.width);
	while (start <= end)
	{
		if (str[x][start] != '1' && str[x][start] != ' ')
			return (print_and_return(ERR_LL, 1));
		start++;
	}
	return (0);
}
