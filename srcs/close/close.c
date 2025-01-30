/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:59:40 by tkafanov          #+#    #+#             */
/*   Updated: 2025/01/30 11:11:32 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	destroy_images(t_memory *memory)
{
	if (memory->mlx_data->north_texture)
	{
		mlx_destroy_image(memory->mlx_data->mlx, memory->mlx_data->north_texture);
		memory->mlx_data->north_texture = NULL;
	}
	if (memory->mlx_data->south_texture)
	{
		mlx_destroy_image(memory->mlx_data->mlx, memory->mlx_data->south_texture);
		memory->mlx_data->south_texture = NULL;
	}
	if (memory->mlx_data->west_texture)
	{
		mlx_destroy_image(memory->mlx_data->mlx, memory->mlx_data->west_texture);
		memory->mlx_data->west_texture = NULL;
	}
	if (memory->mlx_data->east_texture)
	{
		mlx_destroy_image(memory->mlx_data->mlx, memory->mlx_data->east_texture);
		memory->mlx_data->east_texture = NULL;
	}
}

void	destroy(t_memory *memory)
{
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
	destroy_images(memory);
}

int	close_game(void)
{
	t_memory	*memory;

	memory = get_memory();
	destroy(memory);
	free_memory();
	exit(0);
	return (0);
}

int	close_game_error(void)
{
	t_memory	*memory;

	memory = get_memory();
	destroy(memory);
	free_memory();
	exit(1);
	return (0);
}
