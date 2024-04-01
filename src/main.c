/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:20:44 by bplante           #+#    #+#             */
/*   Updated: 2024/03/31 23:56:41 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>
#ifndef M_PI
# define M_PI 3.141592653589793
#endif

#define screenWidth 600
#define screenHeight 600

typedef struct s_vector
{
	double	x;
	double	y;
}			t_vector;

typedef struct s_game
{
	int 	*map;
	t_vector pos;
	t_vector look_dir;
	t_vector plane;
}	t_game;

t_vector rotate_vector(const t_vector *v, double angle)
{
	t_vector result;
	result.x = v->x * cos(angle) - v->y * sin(angle);
	double sinus = sin(angle);
	double cosinus = cos(angle);
	result.y = v->x * sin(angle) + v->y * cos(angle);
	return result;
}

double rad_to_deg(double rad)
{
	return rad * 180 / M_PI;
}

t_vector add_vector(const t_vector *v1, const t_vector *v2)
{
	t_vector result;
	result.x = v1->x + v2->x;
	result.y = v1->y + v2->y;
	return result;
}

double deg_to_rad(double deg)
{
	return deg * (M_PI / 180);
}

int	main(void)
{
	t_game game;
	int map[10 * 10] = {
			1,1,1,1,1,1,1,1,1,1,
			1,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,1,
			1,0,0,1,0,1,0,0,0,1,
			1,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,1,
			1,1,1,1,1,1,1,1,1,1 };
	game.pos.x = 1.5;
	game.pos.y = 1.5;
	game.look_dir.x = 0;
	game.look_dir.y = -1;
	game.plane.x = 0;
	game.plane.y = 1;
	game.look_dir = rotate_vector(&game.look_dir, deg_to_rad(90));
	
}