/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopperma <sopperma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 08:41:32 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/18 15:23:06 by sopperma         ###   ########.fr       */
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

void	display(void)
{
	t_memory	*memory;

	memory = get_memory();
	ft_bzero(memory->mlx_data->addr, \
		memory->mlx_data->resolution_x * memory->mlx_data->resolution_y \
		* (memory->mlx_data->bpp / 8));
	cast_rays();
	mlx_put_image_to_window(memory->mlx_data->mlx, memory->mlx_data->window, \
		memory->mlx_data->img, 0, 0);
}
