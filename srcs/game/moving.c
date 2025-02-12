/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 08:33:35 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/12 16:11:09 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void move_forward(void)
{
	t_memory	*memory = get_memory();
	float		move_x = memory->player_pos->dir_x * SPEED;
	float		move_y = memory->player_pos->dir_y * SPEED;
	float		step_x = (move_x != 0) ? (STEP_SIZE * (move_x / fabs(move_x))) : 0;
	float		step_y = (move_y != 0) ? (STEP_SIZE * (move_y / fabs(move_y))) : 0;
	float		distance = 0;

	while (fabs(distance) < fabs(move_x)) {
		float new_x = memory->player_pos->x + step_x;

		if (memory->map[(int)memory->player_pos->y][(int)new_x] == '1')
			break ;

		memory->player_pos->x = new_x;
		distance += step_x;
	}
	distance = 0;
	while (fabs(distance) < fabs(move_y)) {
		float new_y = memory->player_pos->y + step_y;

		if (memory->map[(int)new_y][(int)memory->player_pos->x] == '1')
			break ;

		memory->player_pos->y = new_y;
		distance += step_y;
	}
}

void move_backward(void)
{
	t_memory	*memory = get_memory();
	float		move_x = memory->player_pos->dir_x * SPEED;
	float		move_y = memory->player_pos->dir_y * SPEED;
	float		step_x = (move_x != 0) ? (STEP_SIZE * (move_x / fabs(move_x))) : 0;
	float		step_y = (move_y != 0) ? (STEP_SIZE * (move_y / fabs(move_y))) : 0;
	float		distance = 0;

	while (fabs(distance) < fabs(move_x)) {
		float new_x = memory->player_pos->x - step_x;

		if (memory->map[(int)memory->player_pos->y][(int)new_x] == '1')
			break ;

		memory->player_pos->x = new_x;
		distance += step_x;
	}
	distance = 0;
	while (fabs(distance) < fabs(move_y)) {
		float new_y = memory->player_pos->y - step_y;

		if (memory->map[(int)new_y][(int)memory->player_pos->x] == '1')
			break ;

		memory->player_pos->y = new_y;
		distance += step_y;
	}
}

void	move_left(void)
{
	t_memory	*memory = get_memory();
	float		move_x = memory->player_pos->dir_y * SPEED;
	float		move_y = -memory->player_pos->dir_x * SPEED;
	float		step_x = (move_x != 0) ? (STEP_SIZE * (move_x / fabs(move_x))) : 0;
	float		step_y = (move_y != 0) ? (STEP_SIZE * (move_y / fabs(move_y))) : 0;
	float		distance = 0;

	while (fabs(distance) < fabs(move_x)) {
		float new_x = memory->player_pos->x + step_x;

		if (memory->map[(int)memory->player_pos->y][(int)new_x] == '1')
			break ;

		memory->player_pos->x = new_x;
		distance += step_x;
	}
	distance = 0;
	while (fabs(distance) < fabs(move_y)) {
		float new_y = memory->player_pos->y + step_y;

		if (memory->map[(int)new_y][(int)memory->player_pos->x] == '1')
			break ;

		memory->player_pos->y = new_y;
		distance += step_y;
	}
}

void	move_right(void)
{
	t_memory	*memory = get_memory();
	float		move_x = -memory->player_pos->dir_y * SPEED;
	float		move_y = memory->player_pos->dir_x * SPEED;
	float		step_x = (move_x != 0) ? (STEP_SIZE * (move_x / fabs(move_x))) : 0;
	float		step_y = (move_y != 0) ? (STEP_SIZE * (move_y / fabs(move_y))) : 0;
	float		distance = 0;

	while (fabs(distance) < fabs(move_x)) {
		float new_x = memory->player_pos->x + step_x;

		if (memory->map[(int)memory->player_pos->y][(int)new_x] == '1')
			break ;

		memory->player_pos->x = new_x;
		distance += step_x;
	}
	distance = 0;
	while (fabs(distance) < fabs(move_y)) {
		float new_y = memory->player_pos->y + step_y;

		if (memory->map[(int)new_y][(int)memory->player_pos->x] == '1')
			break ;

		memory->player_pos->y = new_y;
		distance += step_y;
	}
}
