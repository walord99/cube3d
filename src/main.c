/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:20:44 by bplante           #+#    #+#             */
/*   Updated: 2024/04/02 15:13:56 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "libft.h"
#include <float.h>
#include <math.h>
#ifndef M_PI
# define M_PI 3.141592653589793
#endif

#define screenWidth 600
#define screenHeight 600

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_game
{
	int			*map;
	t_vector	pos;
	t_vector	look_dir;
	t_vector	plane;
	mlx_t		*mlx;
	mlx_image_t	*rendered;
}				t_game;

t_vector	rotate_vector(const t_vector v, double angle)
{
	t_vector	result;

	result.x = v.x * cos(angle) - v.y * sin(angle);
	result.y = v.x * sin(angle) + v.y * cos(angle);
	return (result);
}

double	rad_to_deg(double rad)
{
	return (rad * 180 / M_PI);
}

t_vector	add_vector(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return (result);
}

double	deg_to_rad(double deg)
{
	return (deg * (M_PI / 180));
}

t_vector	multiply_vector(t_vector v, double mult)
{
	t_vector	result;

	result.x = v.x * mult;
	result.y = v.y * mult;
	return (result);
}

double	dbl_abs(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

uint32_t rbga_builder(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	cast_rays(t_game *game, int *map)
{
	double		cameraX;
	int			mapX;
	int			mapY;
	t_vector	rayDir;
	t_vector	sideDist;
	t_vector	deltaDist;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			x;
	int			y;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;

	x = 0;
	while (x < screenWidth)
	{
		cameraX = 2 * x / (double)screenWidth - 1;
		rayDir = add_vector(game->look_dir, multiply_vector(game->plane,
					cameraX));
		mapX = game->pos.x / 1;
		mapY = game->pos.y / 1;
		if (rayDir.x == 0)
			deltaDist.x = DBL_MAX;
		else
			deltaDist.x = dbl_abs(1 / rayDir.x);
		if (rayDir.y == 0)
			deltaDist.y = DBL_MAX;
		else
			deltaDist.y = dbl_abs(1 / rayDir.y);
		if (rayDir.x < 0)
		{
			stepX = -1;
			sideDist.x = (game->pos.x - mapX) * deltaDist.x;
		}
		else
		{
			stepX = 1;
			sideDist.x = (1 + mapX - game->pos.x) * deltaDist.x;
		}
		if (rayDir.y < 0)
		{
			stepY = -1;
			sideDist.y = (game->pos.y - mapY) * deltaDist.y;
		}
		else
		{
			stepY = 1;
			sideDist.y = (1 + mapY - game->pos.y) * deltaDist.y;
		}
		hit = 0;
		while (hit == 0)
		{
			if (sideDist.x < sideDist.y)
			{
				sideDist.x += deltaDist.x;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDist.y += deltaDist.y;
				;
				mapY += stepY;
				side = 1;
			}
			if (map[mapX * 10 + mapY] != 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = sideDist.x - deltaDist.x;
		else
			perpWallDist = sideDist.y - deltaDist.y;
		lineHeight = screenHeight / perpWallDist;
		drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		y = drawStart;
		while (y <= drawEnd)
		{
			if (side == 0)
			mlx_put_pixel(game->rendered, x, y, rbga_builder(255, 255, 255, 255));
			else
			mlx_put_pixel(game->rendered, x, y, rbga_builder(200, 200, 200, 255));
			y++;
		}
		x++;
	}
}

int	main(void)
{
	t_game game;
	int map[10 * 10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1};
	game.pos.x = 1.5;
	game.pos.y = 3.2;
	game.look_dir.x = 0;
	game.look_dir.y = -1;
	game.plane.x = 1;
	game.plane.y = 0;
	game.look_dir = rotate_vector(game.look_dir, deg_to_rad(90));
	game.plane = rotate_vector(game.plane, deg_to_rad(90));
	game.mlx = mlx_init(screenWidth, screenHeight, "cube3d", false);
	game.rendered = mlx_new_image(game.mlx, screenWidth, screenWidth);
	cast_rays(&game, map);
	mlx_image_to_window(game.mlx, game.rendered, 0 ,0);
	mlx_loop(game.mlx);
}