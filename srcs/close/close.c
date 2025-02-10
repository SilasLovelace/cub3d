/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopperma <sopperma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:59:40 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/10 18:49:20 by sopperma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	destroy_images(t_memory *memory)
{
	if (memory->mlx_data->img)
	{
		mlx_destroy_image(memory->mlx_data->mlx, memory->mlx_data->img);
		memory->mlx_data->img = NULL;
	}
	if (memory->mlx_data->textures[NORTH].img)
	{
		mlx_destroy_image(memory->mlx_data->mlx, \
			memory->mlx_data->textures[NORTH].img);
		memory->mlx_data->textures[NORTH].img = NULL;
	}
	if (memory->mlx_data->textures[SOUTH].img)
	{
		mlx_destroy_image(memory->mlx_data->mlx, \
			memory->mlx_data->textures[SOUTH].img);
		memory->mlx_data->textures[SOUTH].img = NULL;
	}
	if (memory->mlx_data->textures[WEST].img)
	{
		mlx_destroy_image(memory->mlx_data->mlx, \
			memory->mlx_data->textures[WEST].img);
		memory->mlx_data->textures[WEST].img = NULL;
	}
	if (memory->mlx_data->textures[EAST].img)
	{
		mlx_destroy_image(memory->mlx_data->mlx, \
			memory->mlx_data->textures[EAST].img);
		memory->mlx_data->textures[EAST].img = NULL;
	}
}

void	destroy(t_memory *memory)
{
	destroy_images(memory);
	if (memory->mlx_data->window && memory->mlx_data->mlx)
	{
		mlx_destroy_window(memory->mlx_data->mlx, memory->mlx_data->window);
		memory->mlx_data->window = NULL;
	}
	if (memory->mlx_data->mlx)
	{
		mlx_destroy_display(memory->mlx_data->mlx);
		free(memory->mlx_data->mlx);
		memory->mlx_data->mlx = NULL;
	}
}

int	close_game(void)
{
	t_memory	*memory;

	memory = get_memory();
	free_memory();
	exit(0);
	return (0);
}

int	close_game_error(void)
{
	t_memory	*memory;

	memory = get_memory();
	free_memory();
	exit(1);
	return (1);
}
