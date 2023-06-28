/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbhooks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:08:40 by sacorder          #+#    #+#             */
/*   Updated: 2023/06/28 17:44:50 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	kb_rotations_hook(int key, t_fdf *fdf)
{
	if (key == ROTATE_UP_KEY)
		//mlx ROTATE UP
	if (key == ROTATE_LEFT_KEY)
		//mlx ROTATE LEFT
	if (key == ROTATE_DOWN_KEY)
		//mlx ROTATE DOWN
	if (key == ROTATE_RIGHT_KEY)
		//mlx ROTATE RIGHT
}

void	keyboard_hook(int key, void *param)
{
	t_fdf *fdf;

	fdf = param;
	kb_rotations_hook(key, fdf);
	if (key == HELP_KEY)
		//mlx toogle help
	
}