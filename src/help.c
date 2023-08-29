/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 00:52:06 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/30 01:22:43 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	draw_help(t_img *img, t_fdf *fdf)
{
	int	i;
	int	j;
	int	step;

	i = -1;
	step = (WIN_HEIGHT - 50) / 6;
	while (++i < WIN_HEIGHT)
	{
		j = -1;
		while (++j < WIN_WIDTH / 8)
			img_pix_put(img, j, i, 0x000000);
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win_ptr, fdf->img.mlx_img, 0, 0);
	mlx_string_put(fdf->mlx, fdf->win_ptr, 20, 25 + (0 * step),
		0xFFFFFF, "Press H for toggle help");
	mlx_string_put(fdf->mlx, fdf->win_ptr, 20, 25 + (1 * step),
		0xFFFFFF, "Use WASD for camera movement");
	mlx_string_put(fdf->mlx, fdf->win_ptr, 20, 25 + (2 * step),
		0xFFFFFF, "Q/E counter/clockwise rotation");
	mlx_string_put(fdf->mlx, fdf->win_ptr, 20, 25 + (3 * step),
		0xFFFFFF, "Z/X zoom in/zoom out");
	mlx_string_put(fdf->mlx, fdf->win_ptr, 20, 25 + (4 * step),
		0xFFFFFF, "V/B v_scale inc/dec");
	mlx_string_put(fdf->mlx, fdf->win_ptr, 20, 25 + (5 * step),
		0xFFFFFF, "P change projection");
}
