/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:22:39 by tkafanov          #+#    #+#             */
/*   Updated: 2025/01/30 11:06:19 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int handle_input(int key, t_memory *memory)
{
	if (!memory)
		return (1);
	if (key == XK_Escape)
		close_game();
	return (SUCCESS);
}

void	take_images()
{
	t_memory	*memory;
	int			width;
	int			height;

	width = 512;
	height = 512;
	memory = get_memory();
	if (!memory || !memory->resources)
	{
		printf("Error\nMemory allocation failed\n");
		return;
	}
	memory->mlx_data->north_texture = mlx_xpm_file_to_image(memory->mlx_data->mlx, memory->resources->north_texture, &width, &height);
	memory->mlx_data->south_texture = mlx_xpm_file_to_image(memory->mlx_data->mlx, memory->resources->south_texture, &width, &height);
	memory->mlx_data->west_texture = mlx_xpm_file_to_image(memory->mlx_data->mlx, memory->resources->west_texture, &width, &height);
	memory->mlx_data->east_texture = mlx_xpm_file_to_image(memory->mlx_data->mlx, memory->resources->east_texture, &width, &height);
	if (!memory->mlx_data->north_texture || !memory->mlx_data->south_texture || !memory->mlx_data->west_texture || !memory->mlx_data->east_texture)
	{
		printf("Error\nTexture allocation failed\n");
		close_game_error();
	}
}

void run_game(void)
{
	t_memory *memory;

	memory = get_memory();
	if (!memory || !memory->resources)
	{
		printf("Error\nMemory allocation failed\n");	
		return;
	}
	memory->mlx_data->mlx = mlx_init();
	if (!memory->mlx_data->mlx)
	{
		printf("Error\nMLX initialization failed\n");
		return;
	}
	memory->mlx_data->window = mlx_new_window(memory->mlx_data->mlx, 640, 480, "cub3D");
	if (!memory->mlx_data->window)
	{
		printf("Error\nWindow creation failed\n");
		mlx_destroy_display(memory->mlx_data->mlx);
		free(memory->mlx_data->mlx);
		memory->mlx_data->mlx = NULL;
		return;
	}
	
	mlx_key_hook(memory->mlx_data->window, handle_input, memory);
	mlx_hook(memory->mlx_data->window, DestroyNotify, StructureNotifyMask, &close_game, memory);
	display();
	mlx_loop(memory->mlx_data->mlx);
}
