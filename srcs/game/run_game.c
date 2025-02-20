/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:22:39 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/19 17:35:34 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	action(void)
{
	if (get_memory()->keys->w_pressed)
		move_forward();
	if (get_memory()->keys->s_pressed)
		move_backward();
	if (get_memory()->keys->a_pressed)
		move_left();
	if (get_memory()->keys->d_pressed)
		move_right();
	if (get_memory()->keys->left_pressed)
		rotate_left();
	if (get_memory()->keys->right_pressed)
		rotate_right();
}

static int	game_loop(t_memory *memory)
{
	if (memory->keys->w_pressed || memory->keys->s_pressed
		|| memory->keys->a_pressed || memory->keys->d_pressed
		|| memory->keys->left_pressed || memory->keys->right_pressed)
	{
		action();
		display();
	}
	return (SUCCESS);
}

static void	init_data(void)
{
	t_memory	*memory;

	memory = get_memory();
	memory->mlx_data->mlx = mlx_init();
	if (!memory->mlx_data->mlx)
	{
		printf("Error\nMLX initialization failed\n");
		close_game_error();
	}
	take_images();
	memory->mlx_data->window = mlx_new_window(memory->mlx_data->mlx, \
		memory->mlx_data->resolution_x, memory->mlx_data->resolution_y, \
			"cub3D");
	if (!memory->mlx_data->window)
	{
		printf("Error\nWindow creation failed\n");
		close_game_error();
	}
}

void	run_game(void)
{
	t_memory	*memory;

	memory = get_memory();
	init_data();
	memory->mlx_data->img = mlx_new_image(memory->mlx_data->mlx, \
		memory->mlx_data->resolution_x, memory->mlx_data->resolution_y);
	if (!memory->mlx_data->img)
		close_game_error();
	memory->mlx_data->addr = mlx_get_data_addr(memory->mlx_data->img, \
		&memory->mlx_data->bpp, &memory->mlx_data->line_length, \
		&memory->mlx_data->endian);
	if (!memory->mlx_data->addr)
		close_game_error();
	mlx_loop_hook(memory->mlx_data->mlx, game_loop, memory);
	mlx_hook(memory->mlx_data->window, DestroyNotify, StructureNotifyMask, \
		&close_game, memory);
	mlx_hook(memory->mlx_data->window, KeyPress, KeyPressMask, \
		handle_keypress, memory);
	mlx_hook(memory->mlx_data->window, KeyRelease, KeyReleaseMask, \
		handle_keyrelease, memory);
	display();
	mlx_loop(memory->mlx_data->mlx);
}
