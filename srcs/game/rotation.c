/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:25:34 by tkafanov          #+#    #+#             */
/*   Updated: 2025/01/31 14:15:59 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate_right(void)
{
	t_memory	*memory;
	float		old_dir_x;

	memory = get_memory();
	old_dir_x = memory->player_pos->dir_x;
	memory->player_pos->dir_x = memory->player_pos->dir_x * cos(ROT_SPEED) \
		- memory->player_pos->dir_y * sin(ROT_SPEED);
	memory->player_pos->dir_y = old_dir_x * sin(ROT_SPEED) \
		+ memory->player_pos->dir_y * cos(ROT_SPEED);
	memory->player_pos->angle = atan2f(memory->player_pos->dir_y, \
		memory->player_pos->dir_x);
}

void	rotate_left(void)
{
	t_memory	*memory;
	float		old_dir_x;

	memory = get_memory();
	old_dir_x = memory->player_pos->dir_x;
	memory->player_pos->dir_x = memory->player_pos->dir_x * cos(-ROT_SPEED) \
		- memory->player_pos->dir_y * sin(-ROT_SPEED);
	memory->player_pos->dir_y = old_dir_x * sin(-ROT_SPEED) \
		+ memory->player_pos->dir_y * cos(-ROT_SPEED);
	memory->player_pos->angle = atan2f(memory->player_pos->dir_y, \
		memory->player_pos->dir_x);
}
