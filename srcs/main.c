/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:29:03 by sopperma          #+#    #+#             */
/*   Updated: 2025/02/20 10:04:42 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_valid_map_name(char *map_name)
{
	char	*last_dot;

	last_dot = ft_strrchr(map_name, '.');
	return (last_dot && ft_strncmp(last_dot, ".cub", 4) == 0
		&& last_dot[4] == '\0' && ft_strlen(map_name) > 4
		&& *(last_dot - 1) != '/');
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (get_memory() == NULL)
			return (printf("Error\nMemory allocation failed\n"), 1);
		if (is_valid_map_name(av[1]))
		{
			if (parse_map(av))
				return (free_memory(), 1);
			run_game();
		}
		else
			return (printf("Error\nInvalid map name: %s\n", av[1]), \
			free_memory(), 1);
		free_memory();
	}
	else
		printf("Error\nInvalid number of arguments!\n");
	return (0);
}
