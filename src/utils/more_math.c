/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:36:31 by bplante           #+#    #+#             */
/*   Updated: 2024/04/16 09:40:47 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg_to_rad(double deg)
{
	return (deg * (M_PI / 180));
}

double	dbl_abs(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

double	fast_inv_sqrt(double n)
{
	long		i;
	const float	threehalfs = 1.5F;

	float x2, y;
	x2 = n * 0.5F;
	y = n;
	i = *(long *)&y;           // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1); // what the fuck?
	y = *(float *)&i;
	y = y * (threehalfs - (x2 * y * y));
	return (y);
}
