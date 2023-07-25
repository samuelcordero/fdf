/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:08:40 by sacorder          #+#    #+#             */
/*   Updated: 2023/07/25 22:53:23 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	hook_exit(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->win_ptr);
	exit(0);
	return (0);
}

int	ft_input_hook(int keycode, t_fdf *fdf)
{
	(void) fdf;
	ft_printf("Key code: %i\n", keycode);
	if (keycode == ESCAPE)
		hook_exit(fdf);
	return (0);
}

/* static void	kb_rotations_hook(int key, t_fdf *fdf)
{
	if (key == ROTATE_UP_KEY)
		//mlx ROTATE UP
	if (key == ROTATE_LEFT_KEY)
		//mlx ROTATE LEFT
	if (key == ROTATE_DOWN_KEY)
		//mlx ROTATE DOWN
	if (key == ROTATE_RIGHT_KEY)
		//mlx ROTATE RIGHT
} */
