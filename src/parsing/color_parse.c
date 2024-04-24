/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:46:13 by yothmani          #+#    #+#             */
/*   Updated: 2024/04/24 18:25:24 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_valid_color_char(char c)
{
	if (ft_isdigit(c) || c == ',' || c == ' ')
		return (true);
	else
		return (false);
}

char	*preprocess_color_str(char *color_str, bool *res, int *comma_count)
{
	int		i;
	char	*color_pref;

	color_pref = ft_strtrim(color_str, " \t");
	if (color_pref[1] == ' ' && (color_pref[0] == 'F' || color_pref[0] == 'C'))
		*res = true;
	else
		return (NULL);
	i = 2;
	while (i < (int)ft_strlen(&color_pref[1]))
	{
		if (!is_valid_color_char(color_pref[i]))
			return (NULL);
		if (color_pref[i] == ',')
			(*comma_count)++;
		i++;
	}
	return (color_pref);
}

bool	validate_color_components(char *color_str)
{
	char	**colors;
	int		i;

	i = 0;
	colors = ft_split(color_str, ',');
	while (i < 3)
	{
		if (0 > ft_atoi(colors[i]) || ft_atoi(colors[i]) > 255)
			return (false);
		i++;
	}
	return (true);
}

bool	is_valid_color_str(char *color_str)
{
	bool	res;
	int		comma_count;
	char	*color_pref;
	char	*trimmed_str;

	res = false;
	comma_count = 0;
	color_pref = preprocess_color_str(color_str, &res, &comma_count);
	if (comma_count != 2)
		return (false);
	else
	{
		trimmed_str = color_pref + 1;
		return (validate_color_components(trimmed_str));
	}
}
