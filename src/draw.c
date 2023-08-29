/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:09:41 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/30 01:24:04 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

static void	render_black_background(t_img *img)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WIN_HEIGHT)
	{
		j = -1;
		while (++j < WIN_WIDTH)
			img_pix_put(img, j, i, 0x000000);
	}
}

int	render(t_fdf *fdf)
{
	if (fdf->win_ptr == NULL)
		return (1);
	render_black_background(&fdf->img);
	ft_project(fdf->map, &fdf->cam);
	if (fdf->cam.angle >= PI2 - PIO4 || fdf->cam.angle < PIO4)
		render_fdf_down(fdf);
	else if (fdf->cam.angle >= PIO4 && fdf->cam.angle < PI - PIO4)
		render_fdf_left(fdf);
	else if (fdf->cam.angle >= PI - PIO4 && fdf->cam.angle < PI + PIO4)
		render_fdf_up(fdf);
	else if (fdf->cam.angle >= PI + PIO4 && fdf->cam.angle < PI2 - PIO4)
		render_fdf_right(fdf);
	if (!fdf->show_help)
	{
		mlx_put_image_to_window(fdf->mlx, fdf->win_ptr,
			fdf->img.mlx_img, 0, 0);
		mlx_string_put(fdf->mlx, fdf->win_ptr, 20, 25,
			0xFFFFFF, "Press H for help");
	}
	else
		draw_help(&fdf->img, fdf);
	return (0);
}
