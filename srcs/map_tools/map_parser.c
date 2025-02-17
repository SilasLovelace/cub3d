/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopperma <sopperma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:43:48 by sopperma          #+#    #+#             */
/*   Updated: 2025/02/17 17:46:47 by sopperma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_number(char *str, char term)
{
	int		i;
	char	*start;

	i = 0;
	start = str;
	while (*str && ft_isdigit(*str))
	{
		str++;
		i++;
	}
	if (i > 3 || (*str != term && *str != '\n') || ft_atoi(start) > 255)
		return (-1);
	return (i);
}

static void calculate_map_dimensions(void)
{
	t_memory *memory = get_memory();
	int max_width = 0;
	int height = 0;

	while (memory->input[height])
	{
		int current_width = ft_strlen(memory->input[height]);
		if (current_width > max_width)
			max_width = current_width;
		height++;
	}
		
	memory->resources->map_width = max_width;
	memory->resources->map_height = height - memory->map_start_row;
}

static void cut_and_fill_map()
{
	int line;
	int x;
	int d;
	int input_len;
		
	x = 0;
	line = get_memory()->map_start_row;
	get_memory()->map = malloc(sizeof(char *) * (get_memory()->resources->map_height + 1));
	while (get_memory()->input[line])
	{
		get_memory()->map[x] = malloc(sizeof(char) * (get_memory()->resources->map_width + 1));
		d = 0;
		input_len = ft_strlen(get_memory()->input[line]);
		while (d < get_memory()->resources->map_width)
		{
			if (d >= input_len || get_memory()->input[line][d] == ' ' ||  get_memory()->input[line][d] == '\n')
				get_memory()->map[x][d] = '1';
			else
				get_memory()->map[x][d] = get_memory()->input[line][d];
			d++;
		}
		get_memory()->map[x][d] = '\0';
		x++;
		line++;
	}
	get_memory()->map[x] = NULL;
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
				printf("Map input valid\n\n");
				cut_and_fill_map();
				print_memory();
			}
			else
				return (1);
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
	return (0);
}
