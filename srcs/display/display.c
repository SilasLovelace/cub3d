/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 08:41:32 by tkafanov          #+#    #+#             */
/*   Updated: 2025/01/30 11:05:11 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	display(void)
{
	t_memory	*memory;
	memory = get_memory();
	if (!memory || !memory->resources)
	{
		printf("Error\nMemory allocation failed\n");
		return;
	}
}