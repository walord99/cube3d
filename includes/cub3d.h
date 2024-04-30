/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:45:12 by yothmani          #+#    #+#             */
/*   Updated: 2024/04/30 14:05:08 by bplante          ###   ########.fr       */
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

# define PLAYER_MOVE_BOX 0.2
# define screenWidth 1920
# define screenHeight 1080

# define MIN_HEIGHT 3
# define MIN_WIDTH 3
# define ERR_ARGC "Error: Invalid arguments. Usage: ./cub3D <file.cub>\n"
# define ERR_BADFILE "Error: Bad file extension\n"

typedef struct s_dbl_vector
{
	double			x;
	double			y;
}					t_dbl_vector;

typedef struct s_int_vector
{
	int				x;
	int				y;
}					t_int_vector;

typedef struct s_raycaster
{
	t_int_vector	map_pos;
	t_int_vector	step;
	t_dbl_vector	rayDir;
	t_dbl_vector	sideDist;
	t_dbl_vector	deltaDist;
	double			perpWallDist;
	double			wallX;
	int				side;
}					t_raycaster;

typedef struct s_draw_info
{
	t_int_vector	screen_pos;
	double			cameraX;
	int				lineHeight;
	int				drawStart;
	int				drawEnd;
	int				texX;
}					t_draw_info;

typedef struct s_game
{
	int				*map;
	t_dbl_vector	pos;
	t_dbl_vector	look_dir;
	t_dbl_vector	plane;
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
t_dbl_vector		multiply_vector(t_dbl_vector v, double mult);
t_dbl_vector		add_vector(t_dbl_vector v1, t_dbl_vector v2);
t_dbl_vector		rotate_vector(const t_dbl_vector v, double angle);
t_dbl_vector		round_off_floating_point_errors(t_dbl_vector v);
t_dbl_vector		normalise_vector(t_dbl_vector v);
double				magnetude(t_dbl_vector v);

// raycasting
t_dbl_vector		cast_ray(t_raycaster *ri, t_game *game, double offset);

// rendering funnctions
void				draw(t_game *game);

// game functions
void				init_game(t_game *game);
t_dbl_vector		collision_detection(t_game *game, t_dbl_vector movement,
						t_dbl_vector movement_dir);
int					get_map_coordinate(int x, int y, int *map);

// math utils
double				inv_sqrt(double n);
double				dbl_abs(double n);
double				deg_to_rad(double deg);
int					clamp(int range_start, int range_end, int num);

#endif