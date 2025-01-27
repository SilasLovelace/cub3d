/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopperma <sopperma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:07:34 by sopperma          #+#    #+#             */
/*   Updated: 2025/01/27 15:44:58 by sopperma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_memory(void)
{
    t_memory    *m;
    
    m = get_memory();

    if (m == NULL)
    {
        printf("Memory empty!\n");
        return ;
    }
    if (m->resources->north_texture)
        printf("North texture: %s\n", m->resources->north_texture);
    if (m->resources->south_texture)
        printf("South texture: %s\n", m->resources->south_texture);
    if (m->resources->west_texture)
        printf("West texture: %s\n", m->resources->west_texture);
    if (m->resources->east_texture)
        printf("East texture: %s\n", m->resources->east_texture);
    printf("Ceiling texture: %d\n", m->resources->ceiling_color);
    printf("Floor color: %d\n", m->resources->floor_color);
}