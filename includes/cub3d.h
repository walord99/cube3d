/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:45:12 by yothmani          #+#    #+#             */
/*   Updated: 2024/05/06 16:38:07 by yothmani         ###   ########.fr       */
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

# define PLAYER_MOVE_BOX 0.4
# define screenWidth 1920
# define screenHeight 1080

# define MIN_HEIGHT 3
# define MAX_HEIGHT 200
# define MIN_WIDTH 3
# define MAX_WIDTH 200
# define ERR_ARGC "ERROR: Invalid arguments. Usage: ./cub3D <file.cub>\n"
# define ERR_BADFILE "ERROR: Bad file extension\n"
# define ERR_C "ERROR: Ceiling color is not valid"
# define ERR_F "ERROR:Floor color is not valid"
# define ERR_NL "ERROR: Empty lines are not permitted between or after map lines!"
# define ERR_DUP_ELEM "ERROR: duplicate element found!"
# define ERR_INV_ELEM "ERROR: Invalid elements!"
# define ERR_INC_MAP "ERROR: Incorrect map!"
# define ERR_EMPTY_MAP "ERROR: Empty map!"
# define ERR_TEX_N "ERROR: path to the north texture is invalid"
# define ERR_TEX_S "ERROR: path to the south texture is invalid"
# define ERR_TEX_E "ERROR: path to the east texture is invalid"
# define ERR_TEX_W "ERROR: path to the west texture is invalid"
# define ERR_FL "ERROR: First line has incorrect character\n"
# define ERR_LL "ERROR: Last line has incorrect character\n"
# define ERR_SP "ERROR: Only one start point is permitted\n"
# define ERR_FLOOD "ERROR: Map is not playable!\n"

typedef struct s_dbl_vector
{
	double				x;
	double				y;
}						t_dbl_vector;

typedef struct s_int_vector
{
	int					x;
	int					y;
}						t_int_vector;

typedef struct s_raycaster
{
	t_int_vector		map_pos;
	t_int_vector		step;
	t_dbl_vector		start_pos;
	t_dbl_vector		rayDir;
	t_dbl_vector		sideDist;
	t_dbl_vector		deltaDist;
	double				perpWallDist;
	double				wallX;
	int					side;
}						t_raycaster;

typedef struct s_draw_info
{
	t_int_vector		screen_pos;
	double				cameraX;
	int					lineHeight;
	int					drawStart;
	int					drawEnd;
	int					texX;
}						t_draw_info;

typedef struct s_element_check
{
	bool				f_color;
	bool				c_color;
	bool				texture_no;
	bool				texture_so;
	bool				texture_we;
	bool				texture_ea;
}						t_element_check;

typedef struct s_textures
{
	mlx_texture_t		*texture_test;
	mlx_image_t			*img_test;
	int					type;
}						t_textures;

typedef struct s_map
{
	unsigned int		height;
	unsigned int		width;
	int					first_map_line;
	char				**grid;
	bool				has_direction;
	t_element_check		checked_element;
	int					spawn_x;
	int					spawn_y;
	char				spawn_direction;
	mlx_t				*mlx;
	uint32_t			floor;
	uint32_t			cieling;
	struct s_textures	textures;
}						t_map;

typedef struct s_game
{
	t_dbl_vector		pos;
	t_dbl_vector		AABB_corners[4];
	t_dbl_vector		look_dir;
	t_dbl_vector		plane;
	t_int_vector		mouse_pos;
	mlx_t				*mlx;
	mlx_image_t			*rendered;
	t_map				map;
}						t_game;

int						first_non_white(char *line);
bool					is_white_space(char c);
bool					is_map_valid(char **str, t_map *map);
int						open_file(char *file_path);
bool					is_valid_tex_prefix(char *tex_pref);
bool					is_valid_color_str(char *color_pref);
int						check_file_extension(char *file_name);
void					free_map(t_map *map);
int						arg_check(int argc, char **argv);
int						parse(int argc, char **argv, t_map *map, int *fd);
void					init_map_struct(t_map *map);
int						read_and_parse_file(int fd, t_map *map);
void					allocate_grid(t_map *map);
void					populate_grid(t_map *map, int fd);
bool					is_valid_tex(t_map *map, char *path_to_tex);
bool					is_map_playable(t_map *map);
bool					print_and_return(char *msg, int status);
void					free_map(t_map *map);
bool					validate_grid_characters(char **str, t_map *map);
bool					handle_start_points(char **str, t_map *map);
int						check_col_start(char **str, int x, int y);
int						check_col_end(char **str, int x, int end);
int						check_first_and_last_line(char **str, t_map map);
int						find_first_non_whitespace(char *line);
int						find_last_non_whitespace(char *line, int width);
int						element_parse(t_map *map, char *current_line, int *fd);
int						handle_error(char *error_msg, char *current_line,
							int fd);
void					get_map_dimensions(t_map *map, char *current_line,
							int *map_start_idx, int *line_counter);
int						verify_checked_elements(t_map *map, char *current_line,
							int *fd);
int						process_map_line(char *current_line, int *line_counter,
							int *map_start_idx, int *fd);
bool					is_line_empty_or_whitespace(char *current_line);
int						create_texture(t_map *map, char *path_to_tex);

// vector functions
t_dbl_vector			multiply_vector(t_dbl_vector v, double mult);
t_dbl_vector			add_vector(t_dbl_vector v1, t_dbl_vector v2);
t_dbl_vector			rotate_vector(const t_dbl_vector v, double angle);
t_dbl_vector			round_off_floating_point_errors(t_dbl_vector v);
t_dbl_vector			normalise_vector(t_dbl_vector v);
double					magnetude(t_dbl_vector v);

// raycasting
t_dbl_vector			cast_ray(t_raycaster *ri, t_map *map);

// rendering funnctions
uint32_t				rbga_builder(int r, int g, int b, int a);
void					draw(t_game *game);

// game functions
void					init_game(t_game *game);
t_dbl_vector			collision_detection(t_game *game, t_dbl_vector movement,
							t_dbl_vector movement_dir);
int						get_map_coordinate(int x, int y, t_map *map);

// math utils
double					inv_sqrt(double n);
double					dbl_abs(double n);
double					deg_to_rad(double deg);
int						clamp(int range_start, int range_end, int num);

// mlx hooks
void					loop_hook(void *param);
void					mouse_hook(double xpos, double ypos, void *param);
void					key_hook(mlx_key_data_t key_data, void *param);

#endif