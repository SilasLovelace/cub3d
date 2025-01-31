/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:22:39 by tkafanov          #+#    #+#             */
/*   Updated: 2025/01/31 09:27:32 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int handle_keypress(int key, t_memory *memory)
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

int handle_keyrelease(int key, t_memory *memory)
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
		move_forward();
	if (memory->keys->s_pressed)
		move_backward();
	if (memory->keys->a_pressed)
		move_left();
	if (memory->keys->d_pressed)
		move_right();
	if (memory->keys->left_pressed)
		rotate_left();
	if (memory->keys->right_pressed)
		rotate_right();
		
	display();
	return (SUCCESS);
}

void	take_images(void)
{
	t_memory	*memory;
	int			width;
	int			height;

	memory = get_memory();
	get_texture_dimensions(memory->resources->north_texture);
	memory->mlx_data->north_texture = \
		mlx_xpm_file_to_image(memory->mlx_data->mlx, \
			memory->resources->north_texture, &width, &height);
	memory->mlx_data->south_texture = \
		mlx_xpm_file_to_image(memory->mlx_data->mlx, \
			memory->resources->south_texture, &width, &height);
	memory->mlx_data->west_texture = \
		mlx_xpm_file_to_image(memory->mlx_data->mlx, \
			memory->resources->west_texture, &width, &height);
	memory->mlx_data->east_texture = \
		mlx_xpm_file_to_image(memory->mlx_data->mlx, \
			memory->resources->east_texture, &width, &height);
	if (!memory->mlx_data->north_texture || !memory->mlx_data->south_texture
		|| !memory->mlx_data->west_texture || !memory->mlx_data->east_texture)
	{
		printf("Error\nTexture allocation failed\n");
		close_game_error();
	}
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
	mlx_hook(memory->mlx_data->window, KeyPress, KeyPressMask, 
        handle_keypress, memory);
    mlx_hook(memory->mlx_data->window, KeyRelease, KeyReleaseMask, 
        handle_keyrelease, memory);
	print_memory();
	display();
	mlx_loop(memory->mlx_data->mlx);
}
