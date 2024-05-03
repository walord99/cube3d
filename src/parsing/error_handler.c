/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:54:11 by yothmani          #+#    #+#             */
/*   Updated: 2024/05/03 18:45:01 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	print_and_return(char *msg, int status)
{
	ft_printf_fd(msg, 2);
	return (status);
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
	}
	map->grid = NULL;
	map = NULL;
}
