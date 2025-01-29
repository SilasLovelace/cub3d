/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopperma <sopperma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:29:03 by sopperma          #+#    #+#             */
/*   Updated: 2025/01/29 16:36:34 by sopperma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_memory	*get_memory(void)
{
	static t_memory *memory;

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
        memory->resources->north_texture = NULL;
        memory->resources->south_texture = NULL;
        memory->resources->west_texture = NULL;
        memory->resources->east_texture = NULL;
        memory->resources->ceiling_color = -1;
        memory->resources->floor_color = -1;
        memory->map = NULL;
    }
	return (memory);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (is_valid_map_name(av[1]))
        {
            int resources_full = 0;
            int line = 0;
            get_memory()->map = read_file_lines(av[1]);
            if (!get_memory()->map)
                return (free_memory(), printf("Error! Could not read file: %s\n", av[1]), 1);
            char **temp = get_memory()->map;
            while(temp[line])
            {
                if (resources_full == 0 )
                {
                    if(is_valid_resource(temp[line]) || *(temp[line]) == '\n')
                        line++;
                    else
                    {
                        printf("Error! Invalid resource: %s on line %d\n", temp[line], line + 1);
                        break;
                    }
                }
                if (resources_full == 1)
                {
                    while (*(temp[line]) == '\n' )
                        line++;
                    if (is_valid_map(temp + line))
                        printf("Map input valid\n\n");
                    break;
                }
                if (!resources_full
                    && get_memory()->resources->north_texture
                    && get_memory()->resources->south_texture
                    && get_memory()->resources->west_texture
                    && get_memory()->resources->east_texture
                    && get_memory()->resources->ceiling_color!= -1
                    && get_memory()->resources->floor_color != -1)
                    resources_full = 1;
    
            }
            print_memory();
        }
        else
            return (printf("Error! Invalid map name: %s\n", av[1]), 1);
        free_memory();
        free_memory();

	}
    else
    {
        printf("Error\nInvalid number of arguments!\n");
    }
    
    // run_game();
    
	return (0);
}