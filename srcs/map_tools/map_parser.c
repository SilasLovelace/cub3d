/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopperma <sopperma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:43:48 by sopperma          #+#    #+#             */
/*   Updated: 2025/01/22 16:34:18 by sopperma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	{
		printf("Error! Multiple texture paths for the same direction: %s\n", identifier);
		free_memory();	
	}
	return (NULL);
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
			end_info = skip_non_whitespace(begin_info + 2) - 1;
			if (!(*(end_info + 1) == '\0' || *skip_whitespace(end_info + 1) == '\0') || !get_resource_dest(first_non_ws))
				return (0);
			*get_resource_dest(first_non_ws) = ft_substr(begin_info, 0, end_info - begin_info + 1);
			return (1);
		}
	}
	// if (ft_strncmp(first_non_ws, "S ", 2)
	// || ft_strncmp(first_non_ws, "F ", 2))
	// {
	// 	begin_info = skip_whitespace(first_non_ws + 1);
	// }
	// 	return (0);
	return (0);
}

// int resource_paths_are_valid(char* path)
// {
// 	return (is_valid_map_name(path));
// }