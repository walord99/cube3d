/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:04:35 by bplante           #+#    #+#             */
/*   Updated: 2024/05/23 00:58:45 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dbl_vector	rotate_vector(const t_dbl_vector v, double angle_rad)
{
	t_dbl_vector	result;

	result.x = v.x * cos(angle_rad) - v.y * sin(angle_rad);
	result.y = v.x * sin(angle_rad) + v.y * cos(angle_rad);
	return (result);
}

t_dbl_vector	add_vector(t_dbl_vector v1, t_dbl_vector v2)
{
	t_dbl_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return (result);
}

t_dbl_vector	multiply_vector(t_dbl_vector v, double mult)
{
	t_dbl_vector	result;

	result.x = v.x * mult;
	result.y = v.y * mult;
	return (result);
}

t_dbl_vector	round_off_floating_point_errors(t_dbl_vector v)
{
	if (v.x < 0.001 && v.x > -0.001)
		v.x = 0;
	if (v.y < 0.001 && v.y > -0.001)
		v.y = 0;
	return (v);
}

t_dbl_vector	normalise_vector(t_dbl_vector v)
{
	double	magnetude_sqrd;
	double	inv_square_root;

	if (v.x == 0 && v.y == 0)
		return (v);
	magnetude_sqrd = pow(v.x, 2) + pow(v.y, 2);
	inv_square_root = inv_sqrt(magnetude_sqrd);
	v.x *= inv_square_root;
	v.y *= inv_square_root;
	return (v);
}
