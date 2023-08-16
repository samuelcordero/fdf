/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:08:40 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/16 16:45:44 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	hook_exit(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->win_ptr);
	exit(0);
	return (0);
}

static void	kb_rotations_hook(int key, t_fdf *fdf)
{
	if (key == ZOOM_IN)
		fdf->map->h_tile_size += 1;
	else if (key == ZOOM_OUT)
	{
		if (fdf->map->h_tile_size > 1)
			fdf->map->h_tile_size -= 1;
	}
	else if (key == ROTATE_LEFT)
		fdf->cam.angle += 0.05;
	else if (key == ROTATE_RIGHT)
		fdf->cam.angle -= 0.05;
	else if (key == MOVE_DOWN)
		fdf->cam.y -= 10;
	else if (key == MOVE_UP)
		fdf->cam.y += 10;
	else if (key == MOVE_LEFT)
		fdf->cam.x += 10;
	else if (key == MOVE_RIGHT)
		fdf->cam.x -= 10;
} 

int	ft_input_hook(int keycode, t_fdf *fdf)
{
	ft_printf("Key code: %i\n", keycode);
	if (keycode == ESCAPE)
		hook_exit(fdf);
	kb_rotations_hook(keycode, fdf);
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
