/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopperma <sopperma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:43:48 by sopperma          #+#    #+#             */
/*   Updated: 2025/01/29 17:05:25 by sopperma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char*	find_next_comma(char* str)
{
	while (*str && *str != ',')
		str++;
	return (str);
}

char* skip_whitespace(char* str)
{
	while (*str && *str == ' ')
		str++;
	return (str);
}

char* skip_non_whitespace(char* str)
{
	while (*str && *str != ' ')
		str++;
	return (str);
}

int	is_valid_map_name(char* map_name)
{
	char *last_dot;
	last_dot = ft_strrchr(map_name, '.');
	return (last_dot && ft_strncmp(last_dot, ".cub", 4) == 0 && last_dot[4] == '\0' && ft_strlen(map_name) > 4 && *(last_dot - 1) != '/');
}

char	**get_resource_dest(char *identifier)
{
	if (!ft_strncmp(identifier, "NO ", 3) && get_memory()->resources->north_texture == NULL)
		return (&(get_memory()->resources->north_texture));
	if (!ft_strncmp(identifier, "SO ", 3) && get_memory()->resources->south_texture == NULL)
		return (&(get_memory()->resources->south_texture));
	if (!ft_strncmp(identifier, "WE ", 3) && get_memory()->resources->west_texture == NULL)
		return (&(get_memory()->resources->west_texture));
	if (!ft_strncmp(identifier, "EA ", 3) && get_memory()->resources->east_texture == NULL)
		return (&(get_memory()->resources->east_texture));
	if ((!ft_strncmp(identifier, "NO ", 3) && get_memory()->resources->north_texture)
		|| (!ft_strncmp(identifier, "SO ", 3) && get_memory()->resources->south_texture)
		|| (!ft_strncmp(identifier, "WE ", 3) && get_memory()->resources->west_texture)
		|| (!ft_strncmp(identifier, "EA ", 3) && get_memory()->resources->east_texture))
		printf("Error! Multiple definitions for the same element: %s\n", identifier);
	return (NULL);
}

int	*get_color_dest(char *identifier)
{
	if (!ft_strncmp(identifier, "C ", 2) && get_memory()->resources->ceiling_color == -1)
		return (&(get_memory()->resources->ceiling_color));
	if (!ft_strncmp(identifier, "F ", 2) && get_memory()->resources->floor_color == -1)
		return (&(get_memory()->resources->floor_color));
	if ((!ft_strncmp(identifier, "C ", 2) && get_memory()->resources->ceiling_color != -1)
		|| (!ft_strncmp(identifier, "F ", 2) && get_memory()->resources->floor_color != -1))
		printf("Error! Multiple definitions for the same element: %s\n", identifier);
	return (NULL);
}
int parse_number(char* str, char term)
{
	int i;
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

int	is_valid_RGB(char *str)
{
	int		color;
	
	if (parse_number(str, ',') >= 0)
	{
		color = ft_atoi(str) * 256 * 256;
		str += parse_number(str, ',') + 1;
	}
	else
		return (-1);
	if (parse_number(str, ',') >= 0)
	{
		color += ft_atoi(str) * 256 ;
		str += parse_number(str, ',') + 1;
	}
	else
		return (-1);
	if (parse_number(str, ' ') >= 0)
		color += ft_atoi(str);
	else
		return (-1);
	return (color);
}

int is_valid_resource(char* line)
{
	char*	first_non_ws;
	char*	begin_info;
	char*	end_info;
	
	first_non_ws = skip_whitespace(line);
	if (!ft_strncmp(first_non_ws, "NO ", 3)
	|| !ft_strncmp(first_non_ws, "SO ", 3)
	|| !ft_strncmp(first_non_ws, "WE ", 3)
	|| !ft_strncmp(first_non_ws, "EA ", 3))
	{
		begin_info = skip_whitespace(first_non_ws + 2);
		if (!ft_strncmp(begin_info, "./", 2) && *(begin_info + 2) != ' ')
		{
			end_info = skip_non_whitespace(begin_info + 2);
			if (!(*(end_info) == '\0' || *skip_whitespace(end_info) == '\n') || !get_resource_dest(first_non_ws))
				return (0);
			*(char**)get_resource_dest(first_non_ws) = ft_substr(begin_info, 0, end_info - begin_info);
			return (1);
		}
		return (0);
	}
	else if (!ft_strncmp(first_non_ws, "C ", 2)
	|| !ft_strncmp(first_non_ws, "F ", 2))
	{
		begin_info = skip_whitespace(first_non_ws + 1);
		if (is_valid_RGB(begin_info) >= 0)
		{
			end_info = skip_non_whitespace(begin_info);
			if (!(*(end_info) == '\0' || *skip_whitespace(end_info) == '\n') || !get_color_dest(first_non_ws))
				return (0);
			*get_color_dest(first_non_ws) = is_valid_RGB(begin_info);
			return (1);
		}
		return (0);
	}
	else
		return (0);
}

int is_valid_map(char** map)
{
    int i;
    int j;
    int player_found;
    
    if (!map || !map[0])
        return (0);
    i = 0;
    player_found = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == ' ')
            {
                j++;
                continue;
            }
			if (!ft_strchr("01NSEW\n", map[i][j]))
			{
				printf("Error! Invalid character '%c' at line %d, position %d\n", map[i][j], i + 1, j + 1);
                return (0);
            }
			if (ft_strchr("NSEW", map[i][j]))
            {
                if (player_found)
                {
                    printf("Error! Multiple players found at line %d, position %d\n", 
                           i + 1, j + 1);
                    return (0);
                }
                player_found = 1;
            }
			if (ft_strchr("0NSEW", map[i][j]))
            {
                if (i == 0 || !map[i + 1] || j == 0 || !map[i][j + 1])
                {
                    printf("Error! Map not closed at line %d, position %d\n", 
                           i + 1, j + 1);
                    return (0);
                }
                if (j >= (int)ft_strlen(map[i - 1]) || j >= (int)ft_strlen(map[i + 1]) ||
                    map[i - 1][j] == ' ' || map[i + 1][j] == ' ' ||
                    map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
                {
                    printf("Error! Map not properly closed at line %d, position %d\n", 
                           i + 1, j + 1);
                    return (0);
                }
            }
            j++;
        }
        i++;
    }
    if (!player_found)
    {
        printf("Error! No player found in map\n");
        return (0);
    }
    return (1);
}
