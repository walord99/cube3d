/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:40:51 by joe_jam           #+#    #+#             */
/*   Updated: 2024/04/19 16:47:02 by yothmani         ###   ########.fr       */
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
    if(fd < 0)
        return 1;
    else
    {
        map = init_map_struct();
        if (!map)
        {
            free_map(map);
            close(fd);
            return (1);
        }
        if(read_and_parse_file(fd, map))
            return(1);
        fd = file_check(argv);
        if (fd == -1)
        {
			free_map(map);
            close(fd);
            return (1);
        }
        allocate_grid(map);
        populate_grid(map, fd);
        if (!is_map_valid(map->grid, *map))
		{
			free_map(map);		
			return(1);
		}
    }
    close(fd);
	free_map(map);
    return (0);
}

