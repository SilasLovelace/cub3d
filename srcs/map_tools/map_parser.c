/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:43:48 by sopperma          #+#    #+#             */
/*   Updated: 2025/02/17 13:57:39 by tkafanov         ###   ########.fr       */
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

// int check_resource(int line, char **temp)
// {
// 	if (is_valid_resource(temp[line]) || *(temp[line]) == '\n')
// 		line++;
// 	else
// 	{
// 		printf("Error! Invalid resource: %s on line %d\n", \
// 			temp[line], line + 1);
// 		return (free_memory(), 1);
// 	}
// 	return (0);
// }

// int	check_map(int line, char **temp)
// {
// 	while (*(temp[line]) == '\n' )
// 		line++;
// 	if (is_valid_map(temp + line))
// 	{
// 		get_memory()->map_start_row = line;
// 		get_memory()->player_pos->y += line;
// 		printf("Map input valid\n\n");
// 		calculate_map_dimensions();
// 	}
// 	else
// 		return (1);
// 	return (0);
// }

void	cut_and_fill_map()
{
	int line;
	int x;
	
	x = 0;
	line = get_memory()->map_start_row;
	get_memory()->map = malloc(sizeof(char *) * (get_memory()->resources->map_height + 1));
	while (get_memory()->input[line])
	{
		get_memory()->map[x] = malloc(sizeof(char) * (get_memory()->resources->map_width));
		int d = 0;
		while (get_memory()->input[line][d] || d < get_memory()->resources->map_width)
		{
			if (get_memory()->input[line][d] == ' ' || d >= (int)ft_strlen(get_memory()->input[line]) - 1)
				get_memory()->map[x][d] = '1';
			else
				get_memory()->map[x][d] = get_memory()->input[line][d];
			d++;
		}
		get_memory()->map[x][d] = '\0';
		if (x == 0 || x == 1)
			printf("d: %d\n", d);
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
				// get_memory()->player_pos->y += line;
				calculate_map_dimensions();
				printf("Map input valid\n\n");
				printf("map height = %d\n", get_memory()->resources->map_height);
				cut_and_fill_map();
				print_memory();
				// while(temp[line])
				// 	printf("%s", temp[line++]);
			
				// get_memory()->actual_map = ft_strdup(temp[line]);

				
				// get_memory()->map_start_row = line;
				// get_memory()->player_pos->y += line;
				// printf("Map input valid\n\n");
				// calculate_map_dimensions();
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
