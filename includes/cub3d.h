/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:45:12 by yothmani          #+#    #+#             */
/*   Updated: 2024/05/24 14:23:47 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <ctype.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
// # include <float.h>

# ifndef M_PI
#  define M_PI 3.141592653589793
# endif

# define DBL_MAX __DBL_MAX__
# define PLAYER_MOVE_BOX 0.4
# define SCREENWIDTH 1920
# define SCREENHEIGHT 1080

# define MIN_HEIGHT 3
# define MAX_HEIGHT 200
# define MIN_WIDTH 3
# define MAX_WIDTH 200

// ERROR MESSAGES
# define ERR_ARGC "ERROR: Invalid arguments. Usage: ./cub3D <file.cub>\n"
# define ERR_BADFILE "ERROR: Bad file extension\n"
# define ERR_C "ERROR: Ceiling color is not valid"
# define ERR_F "ERROR:Floor color is not valid"
# define ERR_DUP_COLOR "ERROR: color is duplicated"
# define ERR_NL \
	"ERROR: Empty lines are not permitted \
between or after map lines!"
# define ERR_DUP_ELEM "ERROR: duplicate element found!"
# define ERR_INV_ELEM "ERROR: Invalid elements!"
# define ERR_MISSING_N_ELEM "ERROR: Path to the north texture not found!"
# define ERR_MISSING_E_ELEM "ERROR: Path to the east texture not found!"
# define ERR_MISSING_W_ELEM "ERROR: Path to the west texture not found!"
# define ERR_MISSING_S_ELEM "ERROR: Path to the south texture not found!"
# define ERR_MISSING_COLOR "ERROR: Missing color element!"
# define ERR_INC_MAP "ERROR: Incorrect map!"
# define ERR_EMPTY_MAP "ERROR: Empty map!"
# define ERR_TEX_N "ERROR: path to the north texture is invalid"
# define ERR_DUP_N_ELEM "ERROR: path to the north texture is duplicated"
# define ERR_TEX_S "ERROR: path to the south texture is invalid"
# define ERR_DUP_S_ELEM "ERROR: path to the south texture is duplicated"
# define ERR_TEX_E "ERROR: path to the east texture is invalid"
# define ERR_DUP_E_ELEM "ERROR: path to the east texture is duplicated"
# define ERR_TEX_W "ERROR: path to the west texture is invalid"
# define ERR_DUP_W_ELEM "ERROR: path to the west texture is duplicated"
# define ERR_FL "ERROR: First line has incorrect character\n"
# define ERR_LL "ERROR: Last line has incorrect character\n"
# define ERR_SP "ERROR: Only one start point is permitted\n"
# define ERR_FLOOD "ERROR: Map is not playable!\n"

// DIRECTIONS
# define NO 0
# define EA 1
# define SO 2
# define WE 3
# define DOOR 4
# define ARROW 5
# define CIRCLE 6
# define TEXTURE_COUNT 7

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
	t_dbl_vector	start_pos;
	t_dbl_vector	ray_dir;
	t_dbl_vector	side_dist;
	t_dbl_vector	delta_dist;
	double			perp_wall_dist;
	double			wall_x;
	int				side;
	bool			do_doors;
}					t_raycaster;

typedef struct s_draw_info
{
	t_int_vector	screen_pos;
	double			camera_x;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	mlx_texture_t	*texture;
}					t_draw_info;

typedef struct s_element_check
{
	bool			f_color;
	bool			c_color;
	int				texture_no;
	int				texture_so;
	int				texture_we;
	int				texture_ea;
}					t_element_check;

typedef struct s_map
{
	unsigned int	height;
	unsigned int	width;
	int				first_map_line;
	int				fd;
	char			**grid;
	bool			has_direction;
	t_element_check	checked_element;
	int				spawn_x;
	int				spawn_y;
	char			spawn_direction;
	mlx_t			*mlx;
	uint32_t		floor;
	uint32_t		cieling;
	mlx_texture_t	**textures;
}					t_map;

typedef struct s_minimap
{
	mlx_image_t		*arrow;
	mlx_image_t		*circle;
	mlx_image_t		*render;
	t_dbl_vector	norm_rot[2];
}					t_minimap;

typedef struct s_door
{
	double			open_track;
	t_int_vector	map_pos;
}					t_door;
typedef struct s_game
{
	t_dbl_vector	pos;
	t_dbl_vector	aabb_corners[4];
	t_dbl_vector	look_dir;
	t_dbl_vector	plane;
	t_int_vector	mouse_pos;
	mlx_t			*mlx;
	mlx_image_t		*rendered;
	mlx_image_t		*fc_img;
	t_minimap		minimap;
	t_map			map;
	t_door			**doors;
}					t_game;

typedef struct s_c2_vars
{
	t_dbl_vector	*mov;
	t_dbl_vector	*mov_dir;
	t_raycaster		*shortest;
	t_dbl_vector	new_pos;
	double			*move_len;
}					t_c2_vars;
typedef struct s_mpcf
{
	int				r2;
	int				x;
	int				y;
	int				delta_y;
	int				delta_x;
	int				d;
}					t_mpcf;

// PARSING FUNCTIONS
int					first_non_white(char *line);
bool				is_white_space(char c);
bool				is_map_valid(char **str, t_map *map);
int					open_file(char *file_path);
bool				is_valid_tex_prefix(char *tex_pref);
bool				is_valid_color_str(char *color_pref);
int					check_file_extension(char *file_name);
void				free_map(t_map *map);
int					arg_check(int argc, char **argv);
int					parse(int argc, char **argv, t_game *game, int *fd);
void				init_map_struct(t_map *map, int fd);
int					read_and_parse_file(int fd, t_map *map);
void				allocate_grid(t_map *map);
void				populate_grid(t_map *map, int fd);
bool				is_valid_tex(char *path_to_tex);
bool				is_map_playable(t_map *map);
bool				print_and_return(char *msg, int status);
void				free_map(t_map *map);
bool				validate_grid_characters(char **str, t_map *map);
bool				handle_start_points(char **str, t_map *map);
int					check_col_start(char **str, int x, int y);
int					check_col_end(char **str, int x, int end);
int					check_first_and_last_line(char **str, t_map map);
int					find_first_non_whitespace(char *line);
int					find_last_non_whitespace(char *line, int width);
int					element_parse(t_map *map, char *current_line, int *fd);
int					handle_error(char *error_msg, char *current_line, int fd);
void				get_map_dimensions(t_map *map, char *current_line,
						int *map_start_idx, int *line_counter);
int					verify_checked_elements(t_map *map, int *fd);
int					process_map_line(char *current_line, int *line_counter,
						int *map_start_idx, int *fd);
bool				is_line_empty_or_whitespace(char *current_line);
int					create_texture(t_map *map, char *path_to_tex,
						int direction);
char				*double_trim(char *current_line);
void				get_floor_color(t_map *map, char *current_line);
void				get_cieling_color(t_map *map, char *current_line);

int					between_lines_check(char *current_line, int *line_counter,
						int *fd);
int					full_color_check(t_map *map, char *current_line, int fd,
						char color_pref);
void				advance_to_next_line(char **current_line, int *line_counter,
						int fd);
void				finalize_map_processing(t_map *map, char *current_line,
						int grid_idx, int line_counter);
int					process_map(t_map *map, char *current_line,
						int *line_counter, int *grid_idx);
int					last_check(t_map *map, char *current_line, int line_counter,
						int grid_idx);
int					full_color_check(t_map *map, char *current_line, int fd,
						char color_pref);
int					full_tex_check(t_map *map, char *current_line,
						int *line_counter, int *grid_idx);
void				free_textures(t_game game);
void				free_game(t_game *game);
// vector functions
t_dbl_vector		multiply_vector(t_dbl_vector v, double mult);
t_dbl_vector		add_vector(t_dbl_vector v1, t_dbl_vector v2);
t_dbl_vector		rotate_vector(const t_dbl_vector v, double angle);
t_dbl_vector		round_off_floating_point_errors(t_dbl_vector v);
t_dbl_vector		normalise_vector(t_dbl_vector v);

// raycasting
t_dbl_vector		cast_ray(t_raycaster *ri, t_game *game);

// rendering funnctions
uint32_t			rbga_builder(int r, int g, int b, int a);
void				draw(t_game *game);
void				fill_square(mlx_image_t *img, uint32_t color,
						t_int_vector start, t_int_vector end);
void				mid_point_circle_fill(int center_x, int center_y, int r,
						t_game *game);
uint32_t			get_texture_color(unsigned int x, unsigned int y,
						mlx_texture_t *tex);
mlx_image_t			*create_floor_ceil_image(t_game *game);

void				get_pixel_color(t_int_vector pixel_pos, t_int_vector center,
						t_game *game);

// dda init
void				get_delta_dist(t_raycaster *ri);
void				get_step_and_side(t_raycaster *ri);
void				step(t_raycaster *ri);
// dda end
void				set_dda_result(t_raycaster *ri, t_dbl_vector *hit_loc);
void				set_door_hit_info(t_raycaster *ri, t_dbl_vector *hit_loc,
						t_door *door);

// game functions
int					init_game(t_game *game);
t_dbl_vector		collision_detection(t_game *game, t_dbl_vector movement,
						t_dbl_vector movement_dir);
char				get_map_loc(unsigned int x, unsigned int y, t_map *map);
t_door				*get_door(int x, int y, t_game *game);

// input handling
t_dbl_vector		get_move_from_input(t_game *game);
void				rotate_player_from_input(t_game *game);
void				rotate_player(t_game *game, double rot);

// math utils
double				inv_sqrt(double n);
double				dbl_abs(double n);
double				deg_to_rad(double deg);
int					clamp(int range_start, int range_end, int num);

// mlx hooks
void				loop_hook(void *param);
void				mouse_hook(double xpos, double ypos, void *param);
void				key_hook(mlx_key_data_t key_data, void *param);

#endif