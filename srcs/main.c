/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:29:03 by sopperma          #+#    #+#             */
/*   Updated: 2025/01/31 10:24:58 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_memory	*get_memory(void)
{
	static t_memory	*memory;

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
		ft_bzero(memory->resources, sizeof(t_map_resources));
		memory->player_pos = malloc(sizeof(t_coordinates));
		if (!memory->player_pos)
		{
			free(memory->resources);
			free(memory);
			return (NULL);
		}
		ft_bzero(memory->player_pos, sizeof(t_coordinates));
		memory->mlx_data = malloc(sizeof(t_mlx_data));
		if (!memory->mlx_data)
		{
			free(memory->resources);
			free(memory->player_pos);
			free(memory);
			return (NULL);
		}
		ft_bzero(memory->mlx_data, sizeof(t_mlx_data));
		memory->keys = malloc(sizeof(t_keys));
		if (!memory->keys)
		{
			free(memory->resources);
			free(memory->player_pos);
			free(memory->mlx_data);
			free(memory);
			return (NULL);
		}
		ft_bzero(memory->keys, sizeof(t_keys));
		memory->mlx_data->resolution_x = 640;
		memory->mlx_data->resolution_y = 480;
		memory->resources->ceiling_color = -1;
		memory->resources->floor_color = -1;
	}
	return (memory);
}

int	main(int ac, char **av)
{
	int		resources_full;
	int		line;
	char	**temp;

	if (ac == 2)
	{
		if (is_valid_map_name(av[1]))
		{
			resources_full = 0;
			line = 0;
			get_memory()->map = read_file_lines(av[1]);
			if (!get_memory()->map)
				return (free_memory(), \
					printf("Error! Could not read file: %s\n", av[1]), 1);
			temp = get_memory()->map;
			while (temp[line])
			{
				if (resources_full == 0)
				{
					if (is_valid_resource(temp[line]) || *(temp[line]) == '\n')
						line++;
					else
					{
						printf("Error! Invalid resource: %s on line %d\n", \
							temp[line], line + 1);
						return (free_memory(), 1);
					}
				}
				if (resources_full == 1)
				{
					while (*(temp[line]) == '\n' )
						line++;
					if (is_valid_map(temp + line))
					{
						get_memory()->map_start_row = line;
						printf("Map input valid\n\n");
					}
					break ;
				}
				if (!resources_full
					&& get_memory()->resources->north_texture
					&& get_memory()->resources->south_texture
					&& get_memory()->resources->west_texture
					&& get_memory()->resources->east_texture
					&& get_memory()->resources->ceiling_color != -1
					&& get_memory()->resources->floor_color != -1)
					resources_full = 1;
			}
			run_game();
		}
		else
			return (printf("Error! Invalid map name: %s\n", av[1]), 1);
		free_memory();
	}
	else
	{
		printf("Error\nInvalid number of arguments!\n");
	}
	return (0);
}
