/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:43:48 by sopperma          #+#    #+#             */
/*   Updated: 2025/02/18 11:13:34 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	calculate_map_dimensions(void)
{
	t_memory	*memory;
	int			max_width;
	int			height;
	int			current_width;

	memory = get_memory();
	max_width = 0;
	height = 0;
	while (memory->input[height])
	{
		current_width = ft_strlen(memory->input[height]);
		if (current_width > max_width)
			max_width = current_width;
		height++;
	}
	memory->resources->map_width = max_width;
	memory->resources->map_height = height - memory->map_start_row;
}

static bool	check_resources(int resources_full)
{
	return (!resources_full
		&& get_memory()->resources->north_texture
		&& get_memory()->resources->south_texture
		&& get_memory()->resources->west_texture
		&& get_memory()->resources->east_texture
		&& get_memory()->resources->ceiling_color != -1
		&& get_memory()->resources->floor_color != -1);
}

int	parse_map(char **av)
{
	int		resources_full;
	int		line;
	char	**temp;

	resources_full = 0;
	line = 0;
	get_memory()->input = read_file_lines(av[1]);
	if (!get_memory()->input)
		return (free_memory(), \
			printf("Error! Could not read file: %s\n", av[1]), 1);
	temp = get_memory()->input;
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
				calculate_map_dimensions();
				cut_and_fill_map();
				// print_memory();
			}
			else
				return (1);
			break ;
		}
		if (check_resources(resources_full))
			resources_full = 1;
	}
	return (0);
}
