/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <bplante@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:04:35 by bplante           #+#    #+#             */
/*   Updated: 2024/04/16 09:05:10 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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