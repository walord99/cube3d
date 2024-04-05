/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:45:12 by yothmani          #+#    #+#             */
/*   Updated: 2024/04/05 14:33:39 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "MLX42/MLX42.h"
# include <ctype.h>
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_map
{
	unsigned int	height;
	unsigned int	width;
	char			**grid;
}					t_map;

bool				is_white_space(char c);
bool				is_char_valid(char **str);
bool				is_map_valid(char **str);
bool				is_valid_tex_prefix(char *tex_pref);
bool				is_valid_color_str(char *color_pref);
int					check_file_extension(char *file_name);

#endif