/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:25:34 by tkafanov          #+#    #+#             */
/*   Updated: 2025/01/31 10:10:10 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void rotate_left(void)
{
	t_memory	*memory;
	float		old_dir_x;
	float		rotation_speed;
	
	memory = get_memory();
	old_dir_x = memory->player_pos->dir_x;
	rotation_speed = 0.05;
	memory->player_pos->dir_x = memory->player_pos->dir_x * cos(rotation_speed) \
		- memory->player_pos->dir_y * sin(rotation_speed);
	memory->player_pos->dir_y = old_dir_x * sin(rotation_speed) \
		+ memory->player_pos->dir_y * cos(rotation_speed);
	memory->player_pos->angle = atan2(memory->player_pos->dir_y, \
		memory->player_pos->dir_x);
}

void rotate_right(void)
{
	t_memory	*memory;
	float		old_dir_x;
	float		rotation_speed;
	
	memory = get_memory();
	old_dir_x = memory->player_pos->dir_x;
	rotation_speed = 0.05;
	memory->player_pos->dir_x = memory->player_pos->dir_x * cos(-rotation_speed) \
		- memory->player_pos->dir_y * sin(-rotation_speed);
	memory->player_pos->dir_y = old_dir_x * sin(-rotation_speed) \
		+ memory->player_pos->dir_y * cos(-rotation_speed);
	memory->player_pos->angle = atan2(memory->player_pos->dir_y, \
		memory->player_pos->dir_x);
}
