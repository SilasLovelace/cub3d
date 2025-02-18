/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:50:45 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/18 11:51:14 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	get_image_by_type(int type, char *tex)
{
	t_memory	*memory;

	memory = get_memory();
	memory->mlx_data->textures[type].img = \
		mlx_xpm_file_to_image(memory->mlx_data->mlx, \
			tex, \
			&memory->mlx_data->textures[type].width, \
			&memory->mlx_data->textures[type].height);
}

static void	get_image_data(int type)
{
	t_memory	*memory;

	memory = get_memory();
	memory->mlx_data->textures[type].addr = \
		mlx_get_data_addr(memory->mlx_data->textures[type].img, \
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
	if (!memory->mlx_data->textures[NORTH].img
		|| !memory->mlx_data->textures[SOUTH].img
		|| !memory->mlx_data->textures[WEST].img
		|| !memory->mlx_data->textures[EAST].img)
	{
		printf("Error\nTexture allocation failed\n");
		close_game_error();
	}
	get_image_data(NORTH);
	get_image_data(SOUTH);
	get_image_data(WEST);
	get_image_data(EAST);
}
