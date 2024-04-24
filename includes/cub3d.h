/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:45:12 by yothmani          #+#    #+#             */
/*   Updated: 2024/04/24 19:15:37 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <ctype.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# ifndef M_PI
#  define M_PI 3.141592653589793
# endif

# define screenWidth 1920
# define screenHeight 1080

# define MIN_HEIGHT 3
# define MIN_WIDTH 3
# define ERR_ARGC "ERROR: Invalid arguments. Usage: ./cub3D <file.cub>\n"
# define ERR_BADFILE "ERROR: Bad file extension\n"
# define ERR_C "ERROR: Ceiling color is not valid"
# define ERR_F "ERROR:Floor color is not valid"
# define ERR_NL "ERROR: Empty lines are not permitted between or after map lines!"
# define ERR_DUP_TEX "ERROR: double texture found!"
# define ERR_INC_ELEM "ERROR: Incomplete elements!"
# define ERR_ELEM "ERROR: Invalid or duplicate element!"
# define ERR_MAP_NOT_CLOSED "ERROR: Map not closed!"
# define ERR_INC_MAP "ERROR: Incorrect map!"
# define ERR_TEX_N "ERROR: path to the north texture is invalid"
# define ERR_TEX_S "ERROR: path to the south texture is invalid"
# define ERR_TEX_E "ERROR: path to the east texture is invalid"
# define ERR_TEX_W "ERROR: path to the west texture is invalid"
# define ERR_FL "ERROR: First line has incorrect character\n"
# define ERR_LL "ERROR: Last line has incorrect character\n"

typedef struct s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_game
{
	int				*map;
	t_vector		pos;
	t_vector		look_dir;
	t_vector		plane;
	mlx_t			*mlx;
	mlx_image_t		*rendered;
	mlx_image_t		*render_time;
}					t_game;

typedef struct s_element_check
{
	bool			f_color;
	bool			c_color;
	bool			texture_no;
	bool			texture_so;
	bool			texture_we;
	bool			texture_ea;
}					t_element_check;

typedef struct s_map
{
	unsigned int	height;
	unsigned int	width;
	int				first_map_line;
	char			**grid;
	bool			has_direction;
	t_element_check	checked_element;
	int				spawn_x;
	int				spawn_y;
	char			spawn_direction;
}					t_map;

int					first_non_white(char *line);
bool				is_white_space(char c);
bool				is_map_valid(char **str, t_map *map);
int					open_file(char *file_path);
bool				is_valid_tex_prefix(char *tex_pref);
bool				is_valid_color_str(char *color_pref);
int					check_file_extension(char *file_name);
void				free_map(t_map *map);
int					file_check(char **argv);
t_map				*init_map_struct(void);
int					read_and_parse_file(int fd, t_map *map);
void				allocate_grid(t_map *map);
void				populate_grid(t_map *map, int fd);
bool				is_valid_tex(char *path_to_tex);
bool				is_map_playable(t_map *map);
#endif