/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:07:16 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/13 14:07:22 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	**get_resource_dest(char *identifier)
{
	if (!ft_strncmp(identifier, "NO ", 3)
		&& get_memory()->resources->north_texture == NULL)
		return (&(get_memory()->resources->north_texture));
	if (!ft_strncmp(identifier, "SO ", 3)
		&& get_memory()->resources->south_texture == NULL)
		return (&(get_memory()->resources->south_texture));
	if (!ft_strncmp(identifier, "WE ", 3)
		&& get_memory()->resources->west_texture == NULL)
		return (&(get_memory()->resources->west_texture));
	if (!ft_strncmp(identifier, "EA ", 3)
		&& get_memory()->resources->east_texture == NULL)
		return (&(get_memory()->resources->east_texture));
	if ((!ft_strncmp(identifier, "NO ", 3)
			&& get_memory()->resources->north_texture)
		|| (!ft_strncmp(identifier, "SO ", 3)
			&& get_memory()->resources->south_texture)
		|| (!ft_strncmp(identifier, "WE ", 3)
			&& get_memory()->resources->west_texture)
		|| (!ft_strncmp(identifier, "EA ", 3)
			&& get_memory()->resources->east_texture))
		printf("Error! Multiple definitions for the same element: \
			%s\n", identifier);
	return (NULL);
}

int	*get_color_dest(char *identifier)
{
	if (!ft_strncmp(identifier, "C ", 2)
		&& get_memory()->resources->ceiling_color == -1)
		return (&(get_memory()->resources->ceiling_color));
	if (!ft_strncmp(identifier, "F ", 2)
		&& get_memory()->resources->floor_color == -1)
		return (&(get_memory()->resources->floor_color));
	if ((!ft_strncmp(identifier, "C ", 2)
			&& get_memory()->resources->ceiling_color != -1)
		|| (!ft_strncmp(identifier, "F ", 2)
			&& get_memory()->resources->floor_color != -1))
		printf("Error! Multiple definitions for the same element: \
			%s\n", identifier);
	return (NULL);
}
