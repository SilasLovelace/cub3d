/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:29:03 by sopperma          #+#    #+#             */
/*   Updated: 2025/01/27 18:08:58 by tkafanov         ###   ########.fr       */
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
            get_memory()->map = read_file_lines(av[1]);
            if (!get_memory()->map)
                return (free_memory(), printf("Error! Could not read file: %s\n", av[1]), 1);
            while(*get_memory()->map)
            {
                if(is_valid_resource(*get_memory()->map) || *(*get_memory()->map) == '\n')
                    get_memory()->map++;
                else
                {
                    printf("Error! Invalid resource: %s\n", *get_memory()->map);
                    break;
                }
            }
            print_memory();
        }
        else
            return (printf("Error! Invalid map name: %s\n", av[1]), 1);
        free_memory();
	}
    else
    {
        printf("Error\nInvalid number of arguments!\n");
    }
    
    run_game();
    
	return (0);
}