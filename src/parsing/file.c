/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 01:01:57 by joe_jam           #+#    #+#             */
/*   Updated: 2024/04/11 13:20:32 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	open_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	return (fd);
}

int	check_file_extension(char *file_name)
{
	int	i;
	int	j;

	i = 0;
	while (file_name[i] != '\0')
		i++;
	i--;
	while (i >= 0 && file_name[i] != '.')
		i--;
	if (i < 0 || ft_strncmp(".cub", &file_name[i], 4) != 0)
	{
		printf("Error: Bad file extension\n");
		return (1);
	}
	return (0);
}

bool	is_valid_tex_prefix(char *tex_pref)
{
	if ((tex_pref[0] == 'N' && tex_pref[1] == 'O') || (tex_pref[0] == 'S'
			&& tex_pref[1] == 'O') || (tex_pref[0] == 'W' && tex_pref[1] == 'E')
		|| (tex_pref[0] == 'E' && tex_pref[1] == 'A'))
		return (tex_pref[2] == ' ');
	return (false);
}

bool	is_valid_color_str(char *color_pref)
{
	bool	res;
	int		comma_count;
	int		num;
	size_t	i;

	res = false;
	i = 2;
	comma_count = 0;
	if ((color_pref[0] == 'F' || color_pref[0] == 'C') && color_pref[1] == ' ')
		res = true;
	else
		return (false);
	while (color_pref[i] != '\0')
	{
		if (ft_isdigit(color_pref[i]))
		{
			num = 0;
			while (ft_isdigit(color_pref[i]))
			{
				num = num * 10 + (color_pref[i] - '0');
				i++;
			}
			if (num < 0 || num > 255)
				return (false);
			if (color_pref[i] == ' ')
				i++;
		}
		else if (color_pref[i] == ',')
		{
			comma_count++;
			if (comma_count > 2)
				return (false);
			if (color_pref[i + 1] == ',')
				return (false);
			i++;
		}
		else if (color_pref[i] == ' ')
			i++;
		else
			return (false);
	}
	if (comma_count != 2)
		return (false);
	return (res);
}
