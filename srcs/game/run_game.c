/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopperma <sopperma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:22:39 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/17 18:43:45 by sopperma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_keypress(int key, t_memory *memory)
{
	if (key == XK_Escape)
		close_game();
	if (key == XK_w)
		memory->keys->w_pressed = 1;
	if (key == XK_s)
		memory->keys->s_pressed = 1;
	if (key == XK_a)
		memory->keys->a_pressed = 1;
	if (key == XK_d)
		memory->keys->d_pressed = 1;
	if (key == XK_Left)
		memory->keys->left_pressed = 1;
	if (key == XK_Right)
		memory->keys->right_pressed = 1;
	return (SUCCESS);
}

int	handle_keyrelease(int key, t_memory *memory)
{
	if (key == XK_w)
		memory->keys->w_pressed = 0;
	if (key == XK_s)
		memory->keys->s_pressed = 0;
	if (key == XK_a)
		memory->keys->a_pressed = 0;
	if (key == XK_d)
		memory->keys->d_pressed = 0;
	if (key == XK_Left)
		memory->keys->left_pressed = 0;
	if (key == XK_Right)
		memory->keys->right_pressed = 0;
	return (SUCCESS);
}

int	game_loop(t_memory *memory)
{
	if (memory->keys->w_pressed)
	{
		move_forward();
		display();
	}
	if (memory->keys->s_pressed)
	{
		move_backward();
		display();
	}
	if (memory->keys->a_pressed)
	{
		move_left();
		display();	
	}
	if (memory->keys->d_pressed)
	{
		move_right();
		display();
	}
	if (memory->keys->left_pressed)
	{
		rotate_left();
		display();
	}
	if (memory->keys->right_pressed)
	{
		rotate_right();
		display();
	}
	return (SUCCESS);
}

void	get_image_by_type(int type, char *tex)
{
	t_memory	*memory;

	memory = get_memory();
	memory->mlx_data->textures[type].img = \
		mlx_xpm_file_to_image(memory->mlx_data->mlx, \
			tex, \
			&memory->mlx_data->textures[type].width, \
			&memory->mlx_data->textures[type].height);
}

void	get_image_data(int type)
{
	t_memory	*memory;

	memory = get_memory();
	memory->mlx_data->textures[type].addr = mlx_get_data_addr(memory->mlx_data->textures[type].img, \
		&memory->mlx_data->textures[type].bpp, \
			&memory->mlx_data->textures[type].line_length, \
				&memory->mlx_data->textures[type].endian);
}

void	take_images(void)
{
	t_memory	*memory;

	memory = get_memory();
	get_image_by_type(NORTH, memory->resources->north_texture);
	get_image_by_type(SOUTH, memory->resources->south_texture);
	get_image_by_type(WEST, memory->resources->west_texture);
	get_image_by_type(EAST, memory->resources->east_texture);
	if (!memory->mlx_data->textures[NORTH].img || !memory->mlx_data->textures[SOUTH].img
		|| !memory->mlx_data->textures[WEST].img || !memory->mlx_data->textures[EAST].img)
	{
		printf("Error\nTexture allocation failed\n");
		close_game_error();
	}
	get_image_data(NORTH);
	get_image_data(SOUTH);
	get_image_data(WEST);
	get_image_data(EAST);
}

void	run_game(void)
{
	t_memory	*memory;

	memory = get_memory();
	memory->mlx_data->mlx = mlx_init();
	if (!memory->mlx_data->mlx)
	{
		printf("Error\nMLX initialization failed\n");
		return ;
	}
	take_images();
	memory->mlx_data->window = mlx_new_window(memory->mlx_data->mlx, \
		memory->mlx_data->resolution_x, memory->mlx_data->resolution_y, \
			"cub3D");
	if (!memory->mlx_data->window)
	{
		printf("Error\nWindow creation failed\n");
		mlx_destroy_display(memory->mlx_data->mlx);
		free(memory->mlx_data->mlx);
		memory->mlx_data->mlx = NULL;
		return ;
	}
	memory->mlx_data->img = mlx_new_image(memory->mlx_data->mlx, \
		memory->mlx_data->resolution_x, memory->mlx_data->resolution_y);
	memory->mlx_data->addr = mlx_get_data_addr(memory->mlx_data->img, \
		&memory->mlx_data->bpp, &memory->mlx_data->line_length, \
		&memory->mlx_data->endian);
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
