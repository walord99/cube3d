/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:46:17 by yothmani          #+#    #+#             */
/*   Updated: 2024/04/18 22:29:23 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_valid_tex_prefix(char *tex_str)
{
    char *tex_pref = ft_strtrim(tex_str, " \t");
	if ((tex_pref[0] == 'N' && tex_pref[1] == 'O') || (tex_pref[0] == 'S'
			&& tex_pref[1] == 'O') || (tex_pref[0] == 'W' && tex_pref[1] == 'E')
		|| (tex_pref[0] == 'E' && tex_pref[1] == 'A'))
		return (tex_pref[2] == ' ');
	return (false);
}
