/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:42:38 by yothmani          #+#    #+#             */
/*   Updated: 2024/04/18 20:43:14 by yothmani         ###   ########.fr       */
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
