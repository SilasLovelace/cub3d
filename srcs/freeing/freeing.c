/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopperma <sopperma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:32:08 by sopperma          #+#    #+#             */
/*   Updated: 2025/02/17 17:46:06 by sopperma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_map(void)
{
	t_memory	*m;
	int			i;

	m = get_memory();
	if (m->input)
	{
		i = 0;
		while (m->input[i])
		{
			free(m->input[i]);
			i++;
		}
		free(m->input);
	}
	if (m->map)
	{
		i = 0;
		while (m->map[i])
		{
			free(m->map[i]);
			i++;
		}
		free(m->map);
	}
}

void	free_resources(void)
{
	t_memory	*m;

	m = get_memory();
	if (m->resources)
	{
		if (m->resources->north_texture)
			free(m->resources->north_texture);
		if (m->resources->south_texture)
			free(m->resources->south_texture);
		if (m->resources->west_texture)
			free(m->resources->west_texture);
		if (m->resources->east_texture)
			free(m->resources->east_texture);
		free_map();
		free(m->resources);
	}
}

void	free_memory(void)
{
	t_memory	*m;
	static int	freed = 0;

	if (freed)
		return ;
	m = get_memory();
	free_resources();
	if (m->player_pos)
		free(m->player_pos);
	destroy(m);
	if (m->mlx_data)
		free(m->mlx_data);
	if (m->keys)
		free(m->keys);
	free(m);
	freed = 1;
}
