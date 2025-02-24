/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:20:42 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/19 15:30:32 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_memory	*free_addr(t_memory *memory)
{
	free(memory->resources);
	free(memory->player_pos);
	free(memory->mlx_data);
	free(memory);
	return (NULL);
}

t_memory	*get_memory(void)
{
	static t_memory	*memory;

	if (!memory)
	{
		memory = ft_calloc(sizeof(t_memory), 1);
		if (!memory)
			return (NULL);
		memory->resources = ft_calloc(sizeof(t_map_resources), 1);
		if (!memory->resources)
			return (free_addr(memory));
		memory->player_pos = ft_calloc(sizeof(t_coordinates), 1);
		if (!memory->player_pos)
			return (free_addr(memory));
		memory->mlx_data = ft_calloc(sizeof(t_mlx_data), 1);
		if (!memory->mlx_data)
			return (free_addr(memory));
		memory->keys = ft_calloc(sizeof(t_keys), 1);
		if (!memory->keys)
			return (free_addr(memory));
		memory->mlx_data->resolution_x = SCREEN_WIDTH;
		memory->mlx_data->resolution_y = SCREEN_HEIGHT;
		memory->resources->ceiling_color = -1;
		memory->resources->floor_color = -1;
	}
	return (memory);
}
