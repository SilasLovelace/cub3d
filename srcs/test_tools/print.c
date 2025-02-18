/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:07:34 by sopperma          #+#    #+#             */
/*   Updated: 2025/02/18 11:13:25 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// void	print_memory(void)
// {
// 	t_memory	*m;

// 	m = get_memory();
// 	if (m == NULL)
// 	{
// 		printf("Memory empty!\n");
// 		return ;
// 	}
// 	if (m->resources->north_texture)
// 		printf("North texture: %s\n", m->resources->north_texture);
// 	if (m->resources->south_texture)
// 		printf("South texture: %s\n", m->resources->south_texture);
// 	if (m->resources->west_texture)
// 		printf("West texture: %s\n", m->resources->west_texture);
// 	if (m->resources->east_texture)
// 		printf("East texture: %s\n", m->resources->east_texture);
// 	printf("Ceiling color: %d\n", m->resources->ceiling_color);
// 	printf("Floor color: %d\n", m->resources->floor_color);
// 	printf("Map start row: %d\n", m->map_start_row);
// 	printf("Player position: %f, %f\n", m->player_pos->x, m->player_pos->y);
// 	printf("Player direction: %f, %f\n", m->player_pos->dir_x, \
// 		m->player_pos->dir_y);
// 	printf("Resolution: %d, %d\n", m->mlx_data->resolution_x, \
// 		m->mlx_data->resolution_y);
// 	printf("Texture dimensions: %d, %d\n", m->mlx_data->tex_width, \
// 		m->mlx_data->tex_height);
// 	printf("Map width: %d, height: %d\n", m->resources->map_width, \
// 		m->resources->map_height);
// 	int i = 0;
// 	printf("\nMAP:\n\n");
// 	while (m->map[i])
// 	{
// 		ft_putstr_fd(m->map[i], 1);
// 		ft_putstr_fd("\n", 1);
// 		i++;
// 	}
// 	printf("\n");
// }
