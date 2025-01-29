/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:22:39 by tkafanov          #+#    #+#             */
/*   Updated: 2025/01/29 17:48:18 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int close_game(t_memory *memory)
{
	if (!memory || !memory->resources)
		return (0);
	if (memory->resources->window && memory->resources->mlx)
	{
		mlx_destroy_window(memory->resources->mlx, memory->resources->window);
		memory->resources->window = NULL;
	}
	if (memory->resources->mlx)
	{
		mlx_destroy_display(memory->resources->mlx);
		free(memory->resources->mlx);
		memory->resources->mlx = NULL;
	}
	free_memory();
	exit(0);
	return (0);
}

int handle_input(int key, t_memory *memory)
{
	if (!memory)
		return (1);
	if (key == XK_Escape)
		close_game(memory);
	return (SUCCESS);
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
	memory->resources->mlx = mlx_init();
	if (!memory->resources->mlx)
	{
		printf("Error\nMLX initialization failed\n");
		return;
	}
	memory->resources->window = mlx_new_window(memory->resources->mlx, 640, 480, "cub3D");
	if (!memory->resources->window)
	{
		printf("Error\nWindow creation failed\n");
		mlx_destroy_display(memory->resources->mlx);
		free(memory->resources->mlx);
		memory->resources->mlx = NULL;
		return;
	}
	mlx_key_hook(memory->resources->window, handle_input, memory);
	mlx_hook(memory->resources->window, DestroyNotify, StructureNotifyMask, &close_game, memory);
	mlx_loop(memory->resources->mlx);
}
