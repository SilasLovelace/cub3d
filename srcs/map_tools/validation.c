/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:59:19 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/18 11:00:11 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_chars(char **map, int i, int j)
{
	if (!ft_strchr("01NSEW\n", map[i][j]))
	{
		printf("Error! Invalid character '%c' at line %d, \
			position %d\n", map[i][j], i + 1, j + 1);
		return (0);
	}
	return (1);
}

static int	check_player(int *player_found, char **map, int i, int j)
{
	if (*player_found)
	{
		printf("Error! Multiple players found at line %d, \
			position %d\n", i + 1, j + 1);
		return (0);
	}
	set_player_coordinates(map[i][j], j, i);
	*player_found = 1;
	return (1);
}

static int	check_borders(char **map, int i, int j)
{
	if (i == 0 || !map[i + 1] || j == 0 || !map[i][j + 1])
	{
		printf("Error! Map not closed at line %d, \
			position %d\n", i + 1, j + 1);
		return (0);
	}
	if (j >= (int)ft_strlen(map[i - 1])
		|| j >= (int)ft_strlen(map[i + 1])
		|| ((map[i - 1][j] == ' ' || map[i - 1][j] == '\n'))
		|| (map[i + 1][j] == ' ' || map[i + 1][j] == '\n')
		|| map[i][j - 1] == ' ' || (map[i][j + 1] == ' '
		|| map[i][j + 1] == '\n'))
	{
		printf("Error! Map not properly closed at line %d, position %d\n", \
		i + 1, j + 1);
		return (0);
	}
	return (1);
}

static int	check_map(int i, char **map, int *player_found)
{
	int	j;

	j = 0;
	while (map[i][j])
	{
		if (map[i][j] == ' ')
		{
			j++;
			continue ;
		}
		if (!check_chars(map, i, j))
			return (0);
		if (ft_strchr("NSEW", map[i][j]))
		{
			if (!check_player(player_found, map, i, j))
				return (0);
		}
		if (ft_strchr("0NSEW", map[i][j]))
		{
			if (!check_borders(map, i, j))
				return (0);
		}
		j++;
	}
	return (1);
}

int	is_valid_map(char **map)
{
	int	i;
	int	player_found;

	if (!map || !map[0])
		return (0);
	i = 0;
	player_found = 0;
	while (map[i])
	{
		if (!check_map(i, map, &player_found))
			return (0);
		i++;
	}
	if (!player_found)
	{
		printf("Error! No player found in map\n");
		return (0);
	}
	return (1);
}
