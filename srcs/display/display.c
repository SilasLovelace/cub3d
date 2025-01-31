/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 08:41:32 by tkafanov          #+#    #+#             */
/*   Updated: 2025/01/31 09:17:45 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(int x, int y, int color)
{
	t_memory	*memory;
	char		*dst;

	memory = get_memory();
	dst = memory->mlx_data->addr + \
		(y * memory->mlx_data->line_length + x * (memory->mlx_data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	display_background(void)
{
	t_memory	*memory;
	int			x;
	int			y;

	memory = get_memory();
	y = 0;
	while (y < memory->mlx_data->resolution_y)
	{
		x = 0;
		while (x < memory->mlx_data->resolution_x)
		{
			if (y < memory->mlx_data->resolution_y / 2)
				my_mlx_pixel_put(x, y, memory->resources->ceiling_color);
			else
				my_mlx_pixel_put(x, y, memory->resources->floor_color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(memory->mlx_data->mlx, memory->mlx_data->window, \
		memory->mlx_data->img, 0, 0);
}

void	display(void)
{
	t_memory	*memory;

	memory = get_memory();
	display_background();
	// display_walls();
	printf("Player position: %f, %f\n", memory->player_pos->x, \
		memory->player_pos->y);
	printf("Player direction: %f, %f\n", memory->player_pos->dir_x, \
		memory->player_pos->dir_y);
}
