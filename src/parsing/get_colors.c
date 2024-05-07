/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe_jam <joe_jam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:58:27 by joe_jam           #+#    #+#             */
/*   Updated: 2024/05/07 13:58:28 by joe_jam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_floor_color(t_map *map, char *current_line)
{
	char	*new_current_line;
	char	**split;

	new_current_line = ft_strtrim(current_line, "F");
	split = ft_split(new_current_line, ',');
	map->floor = rbga_builder(ft_atoi(split[0]), ft_atoi(split[1]),
			ft_atoi(split[2]), 255);
}

void	get_cieling_color(t_map *map, char *current_line)
{
	char	*new_current_line;
	char	**split;

	new_current_line = ft_strtrim(current_line, "C");
	split = ft_split(new_current_line, ',');
	map->cieling = rbga_builder(ft_atoi(split[0]), ft_atoi(split[1]),
			ft_atoi(split[2]), 255);
}
