/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:29:03 by sopperma          #+#    #+#             */
/*   Updated: 2025/02/17 11:48:59 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (is_valid_map_name(av[1]))
		{
			if (parse_map(av))
				return (free_memory(), 1);
			run_game();
		}
		else
			return (printf("Error! Invalid map name: %s\n", av[1]), 1);
		free_memory();
	}
	else
		printf("Error\nInvalid number of arguments!\n");
	return (0);
}
