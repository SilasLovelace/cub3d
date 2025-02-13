/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 08:33:35 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/13 13:36:42 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_forward(void)
{
	t_memory	*memory = get_memory();
	float		move_x = memory->player_pos->dir_x * SPEED;
	float		move_y = memory->player_pos->dir_y * SPEED;
	float		new_x, new_y;
	float		step_x, step_y;
	int			steps;

	steps = (int)(fmax(fabs(move_x), fabs(move_y)) / 0.1f) + 1;
	step_x = move_x / steps;
	step_y = move_y / steps;
	for (int i = 0; i < steps; i++) {
		new_x = memory->player_pos->x + step_x;
		new_y = memory->player_pos->y + step_y;
		if (memory->map[(int)memory->player_pos->y][(int)new_x] != '1')
			memory->player_pos->x = new_x;
		if (memory->map[(int)new_y][(int)memory->player_pos->x] != '1')
			memory->player_pos->y = new_y;
		if (memory->map[(int)memory->player_pos->y][(int)new_x] == '1' &&
			memory->map[(int)new_y][(int)memory->player_pos->x] == '1')
			break;
	}
}

void	move_backward(void)
{
	t_memory	*memory = get_memory();
	float		move_x = -memory->player_pos->dir_x * SPEED;
	float		move_y = -memory->player_pos->dir_y * SPEED;
	float		new_x, new_y;
	float		step_x, step_y;
	int			steps;
		
	steps = (int)(fmax(fabs(move_x), fabs(move_y)) / 0.1f) + 1;
	step_x = move_x / steps;
	step_y = move_y / steps;
	for (int i = 0; i < steps; i++) {
		new_x = memory->player_pos->x + step_x;
		new_y = memory->player_pos->y + step_y;
		if (memory->map[(int)memory->player_pos->y][(int)new_x] != '1')
			memory->player_pos->x = new_x;
		if (memory->map[(int)new_y][(int)memory->player_pos->x] != '1')
			memory->player_pos->y = new_y;
		if (memory->map[(int)memory->player_pos->y][(int)new_x] == '1' &&
			memory->map[(int)new_y][(int)memory->player_pos->x] == '1')
			break;
	}
}

void	move_left(void)
{
	t_memory	*memory = get_memory();
	float		move_x = memory->player_pos->dir_y * SPEED;
	float		move_y = -memory->player_pos->dir_x * SPEED;
	float		new_x, new_y;
	float		step_x, step_y;
	int			steps;
		
	steps = (int)(fmax(fabs(move_x), fabs(move_y)) / 0.1f) + 1;
	step_x = move_x / steps;
	step_y = move_y / steps;
	for (int i = 0; i < steps; i++) {
		new_x = memory->player_pos->x + step_x;
		new_y = memory->player_pos->y + step_y;
		if (memory->map[(int)memory->player_pos->y][(int)new_x] != '1')
			memory->player_pos->x = new_x;
		if (memory->map[(int)new_y][(int)memory->player_pos->x] != '1')
			memory->player_pos->y = new_y;
		if (memory->map[(int)memory->player_pos->y][(int)new_x] == '1' &&
			memory->map[(int)new_y][(int)memory->player_pos->x] == '1')
			break;
	}
}

void	move_right(void)
{
	t_memory	*memory = get_memory();
	float		move_x = -memory->player_pos->dir_y * SPEED;
	float		move_y = memory->player_pos->dir_x * SPEED;
	float		new_x, new_y;
	float		step_x, step_y;
	int			steps;
		
	steps = (int)(fmax(fabs(move_x), fabs(move_y)) / 0.1f) + 1;
	step_x = move_x / steps;
	step_y = move_y / steps;
	for (int i = 0; i < steps; i++) {
		new_x = memory->player_pos->x + step_x;
		new_y = memory->player_pos->y + step_y;
		if (memory->map[(int)memory->player_pos->y][(int)new_x] != '1')
			memory->player_pos->x = new_x;
		if (memory->map[(int)new_y][(int)memory->player_pos->x] != '1')
			memory->player_pos->y = new_y;
		if (memory->map[(int)memory->player_pos->y][(int)new_x] == '1' &&
			memory->map[(int)new_y][(int)memory->player_pos->x] == '1')
			break;
	}
}
