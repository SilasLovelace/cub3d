/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:42:57 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/20 09:47:09 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	fill_map_line(char *map_line, char *input_line, int map_width)
{
	int	d;
	int	input_len;

	d = 0;
	input_len = ft_strlen(input_line);
	while (d < map_width)
	{
		if (d >= input_len || input_line[d] == ' ' || input_line[d] == '\n')
			map_line[d] = '1';
		else
			map_line[d] = input_line[d];
		d++;
	}
	map_line[d] = '\0';
}

static void	fill_map(int *x, int *line, int *empty_line)
{
	get_memory()->map[*x] = malloc(sizeof(char) * \
		(get_memory()->resources->map_width + 1));
	if (!get_memory()->map[*x])
		close_game_error();
	if (*empty_line && get_memory()->input[*line][0] != '\n')
	{
		printf("Error\nEmpty line in the map found\n");
		while (*x >= 0)
			free(get_memory()->map[(*x)--]);
		free(get_memory()->map);
		get_memory()->map = NULL;
		close_game_error();
	}
	if (get_memory()->input[*line][0] == '\n')
		*empty_line = 1;
	fill_map_line(get_memory()->map[*x], \
		get_memory()->input[*line], \
		get_memory()->resources->map_width);
	(*x)++;
	(*line)++;
}

void	create_map(void)
{
	int	line;
	int	x;
	int	empty_line;

	x = 0;
	empty_line = 0;
	line = get_memory()->map_start_row;
	get_memory()->map = malloc(sizeof(char *) * \
		(get_memory()->resources->map_height + 1));
	if (!get_memory()->map)
		close_game_error();
	while (get_memory()->input[line])
		fill_map(&x, &line, &empty_line);
	get_memory()->map[x] = NULL;
}
