/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:09:41 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/17 17:44:48 by sacorder         ###   ########.fr       */
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

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
			img_pix_put(img, j++, i, 0x000000);
		++i;
	}
}

void	render_fdf(t_fdf *fdf)
{
	int	i;
	int	j;

	j = -1;
	while (++j < fdf->map->height)
	{
		i = -1;
		while (++i < fdf->map->width)
		{
			if (j + 1 < fdf->map->height
				&& !both_invisible(&fdf->map->arr[j][i],
				&fdf->map->arr[j + 1][i]))
				render_wu_line(&fdf->img, fdf->map->arr[j][i],
					fdf->map->arr[j + 1][i]);
			if (i + 1 < fdf->map->width
				&& !both_invisible(&fdf->map->arr[j][i],
				&fdf->map->arr[j][i + 1]))
				render_wu_line(&fdf->img, fdf->map->arr[j][i],
					fdf->map->arr[j][i + 1]);
		}
	}
}

int	render(t_fdf *fdf)
{
	if (fdf->win_ptr == NULL)
		return (1);
	render_black_background(&fdf->img);
	ft_project_iso(fdf->map, &fdf->cam);
	render_fdf(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win_ptr, fdf->img.mlx_img, 0, 0);
	return (0);
}
