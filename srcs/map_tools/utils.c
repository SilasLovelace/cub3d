/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:56:48 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/17 14:58:30 by tkafanov         ###   ########.fr       */
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

void	set_player_coordinates(char orientation, int x, int y)
{
	t_memory	*memory;

	memory = get_memory();
	memory->player_pos->x = x + 0.5;
	memory->player_pos->y = y + 0.5;
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
	memory->player_pos->angle = atan2f(memory->player_pos->dir_y, \
		memory->player_pos->dir_x);
}
