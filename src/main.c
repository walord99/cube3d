/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:40:51 by joe_jam           #+#    #+#             */
/*   Updated: 2024/04/15 19:21:44 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
    int fd;
    t_map *map;
    int i;

    if (argc != 2)
    {
        printf(ERR_ARGC);
        return (1);
    }
    fd = file_check(argv);
    if (fd != -1)
    {
        map = init_map_struct();
        if (!map)
        {
            close(fd);
            return (1);
        }
        read_and_parse_file(fd, map);
        fd = file_check(argv);
        if (fd == -1)
        {
            close(fd);
			free_map(map);
            return (1);
        }
        allocate_grid(map);
        populate_grid(map, fd);
        close(fd);
        // Print the grid
        for (int row = 0; row < map->height; row++)
        {
            for (int col = 0; col < map->width; col++)
            {
                printf("%c", map->grid[row][col]);
            }
            printf("\n");
        }
        if (is_map_valid(map->grid))
            printf("OK\n");
        else
		{
			free_map(map);		
            printf("KO\n");
			return(1);
		}

    }
	free_map(map);
    return (0);
}

