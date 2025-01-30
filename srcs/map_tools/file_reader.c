/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:37:09 by sopperma          #+#    #+#             */
/*   Updated: 2025/01/30 17:34:59 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	**read_file_lines(const char *filename)
{
	int		fd;
	char	*line;
	char	**lines;
	int		line_count;
	int		i;
	bool	flag;

	flag = false;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line_count = 0;
	while (1)
	{
		line = get_next_line(fd, &flag, false);
		if (!line)
			break ;
		line_count++;
		free(line);
	}
	close(fd);
	lines = malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(lines);
		return (NULL);
	}
	i = 0;
	while (i < line_count)
	{
		lines[i] = get_next_line(fd, &flag, false);
		if (!lines[i])
		{
			while (--i >= 0)
				free(lines[i]);
			free(lines);
			close(fd);
			return (NULL);
		}
		i++;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}
