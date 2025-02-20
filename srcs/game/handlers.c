/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:01:06 by tkafanov          #+#    #+#             */
/*   Updated: 2025/02/18 12:01:27 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_keypress(int key, t_memory *memory)
{
	if (key == XK_Escape)
		close_game();
	if (key == XK_w)
		memory->keys->w_pressed = 1;
	if (key == XK_s)
		memory->keys->s_pressed = 1;
	if (key == XK_a)
		memory->keys->a_pressed = 1;
	if (key == XK_d)
		memory->keys->d_pressed = 1;
	if (key == XK_Left)
		memory->keys->left_pressed = 1;
	if (key == XK_Right)
		memory->keys->right_pressed = 1;
	return (SUCCESS);
}

int	handle_keyrelease(int key, t_memory *memory)
{
	if (key == XK_w)
		memory->keys->w_pressed = 0;
	if (key == XK_s)
		memory->keys->s_pressed = 0;
	if (key == XK_a)
		memory->keys->a_pressed = 0;
	if (key == XK_d)
		memory->keys->d_pressed = 0;
	if (key == XK_Left)
		memory->keys->left_pressed = 0;
	if (key == XK_Right)
		memory->keys->right_pressed = 0;
	return (SUCCESS);
}
