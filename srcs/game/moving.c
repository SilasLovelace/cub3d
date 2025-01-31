/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 08:33:35 by tkafanov          #+#    #+#             */
/*   Updated: 2025/01/31 14:16:30 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_forward(void)
{
	float		new_x;
	float		new_y;
	t_memory	*memory;

	memory = get_memory();
	new_x = memory->player_pos->x + memory->player_pos->dir_x * SPEED;
	new_y = memory->player_pos->y + memory->player_pos->dir_y * SPEED;
	if (memory->map[(int)memory->player_pos->y][(int)new_x] != '1')
		memory->player_pos->x = new_x;
	if (memory->map[(int)new_y][(int)memory->player_pos->x] != '1')
		memory->player_pos->y = new_y;
}

void	move_backward(void)
{
	float		new_x;
	float		new_y;
	t_memory	*memory;

	memory = get_memory();
	new_x = memory->player_pos->x - memory->player_pos->dir_x * SPEED;
	new_y = memory->player_pos->y - memory->player_pos->dir_y * SPEED;
	if (memory->map[(int)memory->player_pos->y][(int)new_x] != '1')
		memory->player_pos->x = new_x;
	if (memory->map[(int)new_y][(int)memory->player_pos->x] != '1')
		memory->player_pos->y = new_y;
}

void	move_right(void)
{
	float		new_x;
	float		new_y;
	t_memory	*memory;

	memory = get_memory();
	new_x = memory->player_pos->x - memory->player_pos->dir_y * SPEED;
	new_y = memory->player_pos->y + memory->player_pos->dir_x * SPEED;
	if (memory->map[(int)memory->player_pos->y][(int)new_x] != '1')
		memory->player_pos->x = new_x;
	if (memory->map[(int)new_y][(int)memory->player_pos->x] != '1')
		memory->player_pos->y = new_y;
}

void	move_left(void)
{
	float		new_x;
	float		new_y;
	t_memory	*memory;

	memory = get_memory();
	new_x = memory->player_pos->x + memory->player_pos->dir_y * SPEED;
	new_y = memory->player_pos->y - memory->player_pos->dir_x * SPEED;
	if (memory->map[(int)memory->player_pos->y][(int)new_x] != '1')
		memory->player_pos->x = new_x;
	if (memory->map[(int)new_y][(int)memory->player_pos->x] != '1')
		memory->player_pos->y = new_y;
}
