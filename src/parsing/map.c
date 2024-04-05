/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:49:31 by yothmani          #+#    #+#             */
/*   Updated: 2024/04/03 02:23:15 by joe_jam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_white_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
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
				printf("Invalid character [%c] was found in line [%d]\n", str[x][y], x);
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

int	line_check(char **str)
{
	int	start;
	int	end;
	int	x;

	start = 0;
	end = strlen(str[0]);
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
	end = strlen(str[x]);
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

bool is_map_valid(char **str)
{
	if(is_char_valid(str) && !line_check(str) && !colonne_check(str))
		return(true);
	return(false);
}