/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:46:13 by yothmani          #+#    #+#             */
/*   Updated: 2024/05/29 16:38:56 by yothmani         ###   ########.fr       */
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

char	*check_color_str(char *color_pref, int *comma_count)
{
	int	i;

	i = 2;
	while (color_pref[i] == ' ')
		i++;
	while (i < (int)strlen(&color_pref[1]))
	{
		if (!is_valid_color_char(color_pref[i]))
			return (NULL);
		if (color_pref[i] == ',')
		{
			while (color_pref[i + 1] == ' ')
				i++;
			if (color_pref[i + 1] == ',' || color_pref[i + 1] == '\n')
				return (NULL);
			(*comma_count)++;
		}
		i++;
	}
	return (color_pref);
}

char	*preprocess_color_str(char *color_str, bool *res, int *comma_count)
{
	char	*color_pref;

	color_pref = ft_strtrim(color_str, " \t");
	if (color_pref[1] == ' ' && (color_pref[0] == 'F' || color_pref[0] == 'C'))
		*res = true;
	else
	{
		free(color_pref);
		return (NULL);
	}
	if (!check_color_str(color_pref, comma_count))
	{
		free(color_pref);
		return (NULL);
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
		{
			free_tab((void **)colors, &free);
			return (false);
		}
		i++;
	}
	free_tab((void **)colors, &free);
	return (true);
}

bool	is_valid_color_str(char *color_str)
{
	bool	res;
	int		comma_count;
	char	*color_pref;
	bool	ret;

	res = false;
	comma_count = 0;
	color_pref = preprocess_color_str(color_str, &res, &comma_count);
	if (!color_pref)
		return (false);
	if (comma_count != 2)
	{
		free(color_pref);
		return (false);
	}
	else
	{
		ret = validate_color_components(color_pref + 1);
		free(color_pref);
		return (ret);
	}
}
