/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:08:40 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/28 17:44:42 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	reset_cam(t_fdf *fdf)
{
	fdf->cam.angle = 0.0;
	fdf->cam.x = 0;
	fdf->cam.y = 0;
	fdf->map->h_tile_size = fdf->map->og_tile_size;
	fdf->cam.v_factor = 1.0;
	fdf->cam.mode = 1;
}

int	hook_exit(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->win_ptr);
	exit(0);
	return (0);
}

static void	kb_rotations_hook(int key, t_fdf *fdf)
{
	if (key == ZOOM_IN)
	{
		if (fdf->map->h_tile_size < 500)
			fdf->map->h_tile_size += 1;
	}
	else if (key == ZOOM_OUT)
	{
		if (fdf->map->h_tile_size > 2)
			fdf->map->h_tile_size -= 1;
	}
	else if (key == ROTATE_LEFT)
		fdf->cam.angle += 0.02;
	else if (key == ROTATE_RIGHT)
		fdf->cam.angle -= 0.02;
	else if (key == MOVE_DOWN)
		fdf->cam.y -= fdf->map->h_tile_size;
	else if (key == MOVE_UP)
		fdf->cam.y += fdf->map->h_tile_size;
	else if (key == MOVE_LEFT)
		fdf->cam.x += fdf->map->h_tile_size;
	else if (key == MOVE_RIGHT)
		fdf->cam.x -= fdf->map->h_tile_size;
	else if (key == RESET_CAM)
		reset_cam(fdf);
	else if (key == CHANGE_PROJ)
		fdf->cam.mode = !fdf->cam.mode;
}

static void	kb_rotations_hook2(int key, t_fdf *fdf)
{
	if (key == V_ZOOM_IN)
		fdf->cam.v_factor -= 0.02;
	else if (key == V_ZOOM_OUT)
		fdf->cam.v_factor += 0.02;
}

int	ft_input_hook(int keycode, t_fdf *fdf)
{
	ft_printf("Key code: %i\n", keycode);
	if (keycode == ESCAPE)
		hook_exit(fdf);
	kb_rotations_hook(keycode, fdf);
	kb_rotations_hook2(keycode, fdf);
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
