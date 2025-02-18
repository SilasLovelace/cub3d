/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:42:57 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/18 17:45:16 by tkafanov         ###   ########.fr       */
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

void	cut_and_fill_map(void)
{
	int	line;
	int	x;

	x = 0;
	line = get_memory()->map_start_row;
	get_memory()->map = malloc(sizeof(char *) * \
		(get_memory()->resources->map_height + 1));
	if (!get_memory()->map)
		close_game_error();
	while (get_memory()->input[line])
	{
		get_memory()->map[x] = malloc(sizeof(char) * \
			(get_memory()->resources->map_width + 1));
		if (!get_memory()->map[x])
			close_game_error();
		fill_map_line(get_memory()->map[x], \
			get_memory()->input[line], \
			get_memory()->resources->map_width);
		x++;
		line++;
	}
	get_memory()->map[x] = NULL;
}
