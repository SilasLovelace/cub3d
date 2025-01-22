/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopperma <sopperma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:29:03 by sopperma          #+#    #+#             */
/*   Updated: 2025/01/22 16:25:01 by sopperma         ###   ########.fr       */
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
    }
	return (memory);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (is_valid_resource(av[1]))
        {
            is_valid_resource(av[1]);
            print_memory();
        }
	}
	
	return (0);
}