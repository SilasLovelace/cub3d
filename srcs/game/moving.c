/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 08:33:35 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/18 12:00:22 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_forward(void)
{
	t_memory	*memory;
	t_move_data	data;
	int			i;

	memory = get_memory();
	data.move_x = memory->player_pos->dir_x * SPEED;
	data.move_y = memory->player_pos->dir_y * SPEED;
	data.steps = (int)(fmax(fabs(data.move_x), \
		fabs(data.move_y)) / 0.1f) + 1;
	data.step_x = data.move_x / data.steps;
	data.step_y = data.move_y / data.steps;
	i = 0;
	while (i < data.steps)
	{
		data.new_x = memory->player_pos->x + data.step_x;
		data.new_y = memory->player_pos->y + data.step_y;
		if (memory->map[(int)memory->player_pos->y][(int)data.new_x] != '1')
			memory->player_pos->x = data.new_x;
		if (memory->map[(int)data.new_y][(int)memory->player_pos->x] != '1')
			memory->player_pos->y = data.new_y;
		if (memory->map[(int)memory->player_pos->y][(int)data.new_x] == '1'
			&& memory->map[(int)data.new_y][(int)memory->player_pos->x] == '1')
			break ;
		i++;
	}
}

void	move_backward(void)
{
	t_memory	*memory;
	t_move_data	data;
	int			i;

	memory = get_memory();
	data.move_x = -memory->player_pos->dir_x * SPEED;
	data.move_y = -memory->player_pos->dir_y * SPEED;
	data.steps = (int)(fmax(fabs(data.move_x), \
		fabs(data.move_y)) / 0.1f) + 1;
	data.step_x = data.move_x / data.steps;
	data.step_y = data.move_y / data.steps;
	i = 0;
	while (i < data.steps)
	{
		data.new_x = memory->player_pos->x + data.step_x;
		data.new_y = memory->player_pos->y + data.step_y;
		if (memory->map[(int)memory->player_pos->y][(int)data.new_x] != '1')
			memory->player_pos->x = data.new_x;
		if (memory->map[(int)data.new_y][(int)memory->player_pos->x] != '1')
			memory->player_pos->y = data.new_y;
		if (memory->map[(int)memory->player_pos->y][(int)data.new_x] == '1'
			&& memory->map[(int)data.new_y][(int)memory->player_pos->x] == '1')
			break ;
		i++;
	}
}

void	move_left(void)
{
	t_memory	*memory;
	t_move_data	data;
	int			i;

	memory = get_memory();
	data.move_x = memory->player_pos->dir_y * SPEED;
	data.move_y = -memory->player_pos->dir_x * SPEED;
	data.steps = (int)(fmax(fabs(data.move_x), \
		fabs(data.move_y)) / 0.1f) + 1;
	data.step_x = data.move_x / data.steps;
	data.step_y = data.move_y / data.steps;
	i = 0;
	while (i < data.steps)
	{
		data.new_x = memory->player_pos->x + data.step_x;
		data.new_y = memory->player_pos->y + data.step_y;
		if (memory->map[(int)memory->player_pos->y][(int)data.new_x] != '1')
			memory->player_pos->x = data.new_x;
		if (memory->map[(int)data.new_y][(int)memory->player_pos->x] != '1')
			memory->player_pos->y = data.new_y;
		if (memory->map[(int)memory->player_pos->y][(int)data.new_x] == '1'
			&& memory->map[(int)data.new_y][(int)memory->player_pos->x] == '1')
			break ;
		i++;
	}
}

void	move_right(void)
{
	t_memory	*memory;
	t_move_data	data;
	int			i;

	memory = get_memory();
	data.move_x = -memory->player_pos->dir_y * SPEED;
	data.move_y = memory->player_pos->dir_x * SPEED;
	data.steps = (int)(fmax(fabs(data.move_x), \
		fabs(data.move_y)) / 0.1f) + 1;
	data.step_x = data.move_x / data.steps;
	data.step_y = data.move_y / data.steps;
	i = 0;
	while (i < data.steps)
	{
		data.new_x = memory->player_pos->x + data.step_x;
		data.new_y = memory->player_pos->y + data.step_y;
		if (memory->map[(int)memory->player_pos->y][(int)data.new_x] != '1')
			memory->player_pos->x = data.new_x;
		if (memory->map[(int)data.new_y][(int)memory->player_pos->x] != '1')
			memory->player_pos->y = data.new_y;
		if (memory->map[(int)memory->player_pos->y][(int)data.new_x] == '1'
			&& memory->map[(int)data.new_y][(int)memory->player_pos->x] == '1')
			break ;
		i++;
	}
}
