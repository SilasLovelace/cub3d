/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopperma <sopperma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:20:42 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/18 15:20:53 by sopperma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_memory	*free_addr(t_memory *memory, int i)
{
	if (i > 0)
		free(memory->resources);
	if (i > 1)
		free(memory->player_pos);
	if (i > 2)
		free(memory->mlx_data);
	free(memory);
	return (NULL);
}

t_memory	*get_memory(void)
{
	static t_memory	*memory;

	if (!memory)
	{
		memory = calloc(sizeof(t_memory), 1);
		if (!memory)
			return (NULL);
		memory->resources = calloc(sizeof(t_map_resources), 1);
		if (!memory->resources)
			return (free_addr(memory, 0));
		memory->player_pos = calloc(sizeof(t_coordinates), 1);
		if (!memory->player_pos)
			return (free_addr(memory, 1));
		memory->mlx_data = calloc(sizeof(t_mlx_data), 1);
		if (!memory->mlx_data)
			return (free_addr(memory, 2));
		memory->keys = calloc(sizeof(t_keys), 1);
		if (!memory->keys)
			return (free_addr(memory, 3));
		memory->mlx_data->resolution_x = 1920;
		memory->mlx_data->resolution_y = 1080;
		memory->resources->ceiling_color = -1;
		memory->resources->floor_color = -1;
	}
	return (memory);
}
