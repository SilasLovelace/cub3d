/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:37:23 by tkafanov          #+#    #+#             */
/*   Updated: 2025/01/30 14:52:36 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void get_texture_dimensions(char *filepath)
{
    char    *line;
    int     fd;
    int     i;
    t_memory *memory;

    memory = get_memory();
    fd = open(filepath, O_RDONLY);
    if (fd < 0)
        return;
    for (int j = 0; j < 3; j++) {
        line = get_next_line(fd, false, false);
        if (line)
            free(line);
    }

    line = get_next_line(fd, false, false);
    if (!line) {
        close(fd);
        return;
    }
    i = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '"'))
        i++;
    memory->mlx_data->tex_width = atoi(line + i);
    
    while (line[i] && line[i] != ' ')
        i++;
    while (line[i] && line[i] == ' ')
        i++;
    memory->mlx_data->tex_height = atoi(line + i);
    
    free(line);
    close(fd);
}