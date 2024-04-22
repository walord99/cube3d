/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:36:31 by bplante           #+#    #+#             */
/*   Updated: 2024/04/17 16:15:35 by bplante          ###   ########.fr       */
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
	double square_root = sqrt(n);
	return 1.0f / square_root;
}
