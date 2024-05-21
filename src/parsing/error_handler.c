/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:54:11 by yothmani          #+#    #+#             */
/*   Updated: 2024/05/21 15:19:39 by yothmani         ###   ########.fr       */
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
	unsigned int	i;

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

int	handle_error(char *error_msg, char *current_line, int fd)
{
	ft_printf_fd("%s\n", 2, error_msg);
	if (current_line)
		free(current_line);
	close(fd);
	return (1);
}
