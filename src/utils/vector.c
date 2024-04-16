/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:04:35 by bplante           #+#    #+#             */
/*   Updated: 2024/04/16 09:39:45 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	rotate_vector(const t_vector v, double angle)
{
	t_vector	result;

	result.x = v.x * cos(angle) - v.y * sin(angle);
	result.y = v.x * sin(angle) + v.y * cos(angle);
	return (result);
}

t_vector	add_vector(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return (result);
}

t_vector	multiply_vector(t_vector v, double mult)
{
	t_vector	result;

	result.x = v.x * mult;
	result.y = v.y * mult;
	return (result);
}

t_vector	round_off_floating_point_errors(t_vector v)
{
	if (v.x < 0.001 && v.x > -0.001)
		v.x = 0;
	if (v.y < 0.001 && v.y > -0.001)
		v.y = 0;
	return (v);
}

t_vector	normalise_vector(t_vector v)
{
	double	magnetude_sqrd;
	double	inv_sqrt;

	magnetude_sqrd = pow(v.x, 2) + pow(v.y, 2);
	inv_sqrt = fast_inv_sqrt(magnetude_sqrd);
	v.x *= inv_sqrt;
	v.y *= inv_sqrt;
	return (v);
}
