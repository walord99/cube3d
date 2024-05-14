/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:36:31 by bplante           #+#    #+#             */
/*   Updated: 2024/05/14 13:48:45 by bplante          ###   ########.fr       */
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

double	inv_sqrt(double n)
{
	double	square_root;

	square_root = sqrt(n);
	return (1.0f / square_root);
}

int	clamp(int range_start, int range_end, int num)
{
	if (num < range_start)
		return (range_start);
	if (num > range_end)
		return (range_end);
	return (num);
}
