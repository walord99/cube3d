/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:45:12 by yothmani          #+#    #+#             */
/*   Updated: 2024/04/22 23:18:35 by bplante          ###   ########.fr       */
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

# define PLAYER_MOVE_BOX 0.1
# define screenWidth 1920
# define screenHeight 1080

# define MIN_HEIGHT 3
# define MIN_WIDTH 3
# define ERR_ARGC "Error: Invalid arguments. Usage: ./cub3D <file.cub>\n"
# define ERR_BADFILE "Error: Bad file extension\n"

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
}					t_map;

int					first_non_white(char *line);
bool				is_white_space(char c);
bool				is_map_valid(char **str);
// bool	is_map_valid(t_map *map);
bool				is_valid_tex_prefix(char *tex_pref);
bool				is_valid_color_str(char *color_pref);
int					check_file_extension(char *file_name);
void				free_map(t_map *map);
int					file_check(char **argv);
t_map				*init_map_struct(void);
int					read_and_parse_file(int fd, t_map *map);
char				**allocate_grid(t_map *map);
void				populate_grid(t_map *map, int fd);

// vector functions
t_vector			multiply_vector(t_vector v, double mult);
t_vector			add_vector(t_vector v1, t_vector v2);
t_vector			rotate_vector(const t_vector v, double angle);
t_vector			round_off_floating_point_errors(t_vector v);
t_vector			normalise_vector(t_vector v);
double				magnetude(t_vector v);

// rendering funnctions
void				cast_rays(t_game *game);

// game functions
void				init_game(t_game *game);

// math utils
double				inv_sqrt(double n);
double				dbl_abs(double n);
double				deg_to_rad(double deg);

int					get_map_coordinate(int x, int y, int *map);

#endif