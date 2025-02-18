/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopperma <sopperma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:56:48 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/18 11:07:47 by sopperma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*find_next_comma(char *str)
{
	while (*str && *str != ',')
		str++;
	return (str);
}

char	*skip_whitespace(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (str);
}

char	*skip_non_whitespace(char *str)
{
	while (*str && *str != ' ')
		str++;
	return (str);
}

static void	set_directions(t_memory *memory, char orientation)
{
	if (orientation == 'N')
	{
		memory->player_pos->dir_x = 0;
		memory->player_pos->dir_y = -1;
	}
	else if (orientation == 'E')
	{
		memory->player_pos->dir_x = 1;
		memory->player_pos->dir_y = 0;
	}
	else if (orientation == 'S')
	{
		memory->player_pos->dir_x = 0;
		memory->player_pos->dir_y = 1;
	}
	else if (orientation == 'W')
	{
		memory->player_pos->dir_x = -1;
		memory->player_pos->dir_y = 0;
	}
}

void	set_player_coordinates(char orientation, int x, int y)
{
	t_memory	*memory;

	memory = get_memory();
	memory->player_pos->x = x + 0.5;
	memory->player_pos->y = y + 0.5;
	set_directions(memory, orientation);
	memory->player_pos->angle = atan2f(memory->player_pos->dir_y, \
		memory->player_pos->dir_x);
	memory->player_pos->angle = atan2(memory->player_pos->dir_y, memory->player_pos->dir_x);
}
