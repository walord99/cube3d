/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:38:56 by yothmani          #+#    #+#             */
/*   Updated: 2024/05/02 14:05:08 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	process_map_line(char *current_line, int *line_counter, int *map_start_idx,
		int *fd)
{
	int	idx;

	idx = first_non_white(current_line);
	if (!is_valid_tex_prefix(current_line) && current_line[idx] != 'F'
		&& current_line[idx] != 'C')
	{
		if (*map_start_idx != -1 && *map_start_idx <= *line_counter)
		{
			ft_printf_fd("Column [%d] is not closed\n", 2, *map_start_idx + 1);
			return (1);
		}
		else
			return (handle_error(ERR_INV_ELEM, current_line, *fd));
	}
	else
		return (handle_error(ERR_DUP_ELEM, current_line, *fd));
	return (0);
}

bool	is_line_empty_or_whitespace(char *current_line)
{
	int	idx;

	idx = first_non_white(current_line);
	return (idx == -1);
}
