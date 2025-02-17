/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopperma <sopperma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:20:42 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/17 16:00:30 by sopperma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_memory	*get_memory(void)
{
	static t_memory	*memory;

	if (!memory)
	{
		memory = malloc(sizeof(t_memory));
		if (!memory)
			return (NULL);
		ft_bzero(memory, sizeof(t_memory));
		memory->resources = malloc(sizeof(t_map_resources));
		if (!memory->resources)
		{
			free(memory);
			return (NULL);
		}
		ft_bzero(memory->resources, sizeof(t_map_resources));
		memory->player_pos = malloc(sizeof(t_coordinates));
		if (!memory->player_pos)
		{
			free(memory->resources);
			free(memory);
			return (NULL);
		}
		ft_bzero(memory->player_pos, sizeof(t_coordinates));
		memory->mlx_data = malloc(sizeof(t_mlx_data));
		if (!memory->mlx_data)
		{
			free(memory->resources);
			free(memory->player_pos);
			free(memory);
			return (NULL);
		}
		ft_bzero(memory->mlx_data, sizeof(t_mlx_data));
		
		memory->keys = malloc(sizeof(t_keys));
		if (!memory->keys)
		{
			free(memory->resources);
			free(memory->player_pos);
			free(memory->mlx_data);
			free(memory->mlx_data->textures);
			free(memory);
			return (NULL);
		}
		ft_bzero(memory->keys, sizeof(t_keys));
		memory->mlx_data->resolution_x = 640;
		memory->mlx_data->resolution_y = 480;
		memory->resources->ceiling_color = -1;
		memory->resources->floor_color = -1;
	}
	return (memory);
}