/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopperma <sopperma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:59:40 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/24 11:51:01 by sopperma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	destroy_image_by_type(int type)
{
	if (get_memory()->mlx_data->textures[type].img)
	{
		mlx_destroy_image(get_memory()->mlx_data->mlx, \
			get_memory()->mlx_data->textures[type].img);
		get_memory()->mlx_data->textures[type].img = NULL;
	}
}

void	destroy_images(t_memory *memory)
{
	if (memory->mlx_data->img)
	{
		mlx_destroy_image(memory->mlx_data->mlx, memory->mlx_data->img);
		memory->mlx_data->img = NULL;
	}
	destroy_image_by_type(NORTH);
	destroy_image_by_type(SOUTH);
	destroy_image_by_type(WEST);
	destroy_image_by_type(EAST);
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
	free_memory();
	exit(0);
	return (0);
}

int	close_game_error(void)
{
	free_memory();
	exit(1);
	return (1);
}
