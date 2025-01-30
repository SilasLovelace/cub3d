/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:32:08 by sopperma          #+#    #+#             */
/*   Updated: 2025/01/30 12:27:06 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_memory(void)
{
    t_memory	*m;
    static int  freed = 0;
    if (freed)
        return;
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
        if (m->map)
        {
            int i = 0;
            while (m->map[i])
            {
                free(m->map[i]);
                i++;
            }
            free(m->map);
        }
        free(m->resources);
    }
    if (m->player_pos)
        free(m->player_pos);
    destroy(m);
    if (m->mlx_data)
        free(m->mlx_data);
    free(m);
    freed = 1;
}
