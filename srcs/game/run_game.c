/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:22:39 by tkafanov          #+#    #+#             */
/*   Updated: 2025/01/27 18:13:01 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game(t_memory *memory)
{
	mlx_destroy_window(memory->resources->mlx, memory->resources->window);
	mlx_destroy_display(memory->resources->mlx);
	free(memory->resources->mlx);
	exit(0);
}

int	handle_input(int key, t_memory *data)
{
	if (key == XK_Escape)
		close_game(data);
	// if (key == XK_Up || key == XK_W || key == XK_w)
	// 	move_up(data);
	// else if (key == XK_Down || key == XK_S || key == XK_s)
	// 	move_down(data);
	// else if (key == XK_Right || key == XK_D || key == XK_d)
	// 	move_right(data);
	// else if (key == XK_Left || key == XK_A || key == XK_a)
	// 	move_left(data);
	return (SUCCESS);
}

void	run_game(void)
{
	t_memory	*memory;

	memory = get_memory();
	if (!memory)
	{
		printf("Error\nMemory allocation failed\n");	
		return ;
	}
	memory->resources->mlx = mlx_init();
	if (!memory->resources->mlx)
	{
		printf("Error\nMLX initialization failed\n");
		free(memory);
		return ;
	}
	memory->resources->window = mlx_new_window(memory->resources->mlx, 640, 480, "cub3D");
	if (!memory->resources->window)
	{
		printf("Error\nWindow creation failed\n");
		mlx_destroy_display(memory->resources->mlx);
        free(memory->resources->mlx);
        free(memory);
		return ;
	}
	mlx_key_hook(memory->resources->window, handle_input, &memory);
	mlx_hook(memory->resources->window, DestroyNotify, StructureNotifyMask, &close_game, memory);
	mlx_loop(memory->resources->mlx);
}