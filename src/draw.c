/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:09:41 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/18 15:03:53 by sacorder         ###   ########.fr       */
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

static void	render_fdf_down(t_fdf *fdf)
{
	int	i;
	int	j;

	j = -1;
	while (++j < fdf->map->height)
	{
		i = -1;
		while (++i < fdf->map->width)
		{
			img_pix_put(&fdf->img, (int)fdf->map->arr[j][i].proy_x,
				(int)fdf->map->arr[j][i].proy_y, fdf->map->arr[j][i].color);
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

static void	render_fdf_up(t_fdf *fdf)
{
	int	i;
	int	j;

	j = fdf->map->height;
	while (--j >= 0)
	{
		i = fdf->map->width;
		while (--i >= 0)
		{
			img_pix_put(&fdf->img, (int)fdf->map->arr[j][i].proy_x,
				(int)fdf->map->arr[j][i].proy_y, fdf->map->arr[j][i].color);
			if (j - 1 > 0
				&& !both_invisible(&fdf->map->arr[j][i],
				&fdf->map->arr[j - 1][i]))
				render_wu_line(&fdf->img, fdf->map->arr[j][i],
					fdf->map->arr[j - 1][i]);
			if (i - 1 > 0
				&& !both_invisible(&fdf->map->arr[j][i],
				&fdf->map->arr[j][i - 1]))
				render_wu_line(&fdf->img, fdf->map->arr[j][i],
					fdf->map->arr[j][i - 1]);
		}
	}
}

static void	render_fdf_left(t_fdf *fdf)
{
	int	i;
	int	j;

	j = fdf->map->height;
	while (--j >= 0)
	{
		i = -1;
		while (++i < fdf->map->width)
		{
			img_pix_put(&fdf->img, (int)fdf->map->arr[j][i].proy_x,
				(int)fdf->map->arr[j][i].proy_y, fdf->map->arr[j][i].color);
			if (j - 1 > 0
				&& !both_invisible(&fdf->map->arr[j][i],
				&fdf->map->arr[j - 1][i]))
				render_wu_line(&fdf->img, fdf->map->arr[j][i],
					fdf->map->arr[j - 1][i]);
			if (i - 1 > 0
				&& !both_invisible(&fdf->map->arr[j][i],
				&fdf->map->arr[j][i - 1]))
				render_wu_line(&fdf->img, fdf->map->arr[j][i],
					fdf->map->arr[j][i - 1]);
		}
	}
}

static void	render_fdf_right(t_fdf *fdf)
{
	int	i;
	int	j;

	j =  -1;
	while (++j < fdf->map->height)
	{
		i = fdf->map->width;
		while (--i >= 0)
		{
			img_pix_put(&fdf->img, (int)fdf->map->arr[j][i].proy_x,
				(int)fdf->map->arr[j][i].proy_y, fdf->map->arr[j][i].color);
			if (j - 1 > 0
				&& !both_invisible(&fdf->map->arr[j][i],
				&fdf->map->arr[j - 1][i]))
				render_wu_line(&fdf->img, fdf->map->arr[j][i],
					fdf->map->arr[j - 1][i]);
			if (i - 1 > 0
				&& !both_invisible(&fdf->map->arr[j][i],
				&fdf->map->arr[j][i - 1]))
				render_wu_line(&fdf->img, fdf->map->arr[j][i],
					fdf->map->arr[j][i - 1]);
		}
	}
}

int	render(t_fdf *fdf)
{
	if (fdf->win_ptr == NULL)
		return (1);
	render_black_background(&fdf->img);
	ft_project_iso(fdf->map, &fdf->cam);
	if (fdf->cam.angle >= PI)
		fdf->cam.angle -= PI;
	else if (fdf->cam.angle < 0)
		fdf->cam.angle += PI;
	printf("Angle: %f\n", fdf->cam.angle);
	if (fdf->cam.angle >= 0 && fdf->cam.angle < PI / 2)
		render_fdf_up(fdf);
	else if (fdf->cam.angle >= PI / 2 && fdf->cam.angle < PI)
		render_fdf_right(fdf);
	else if (fdf->cam.angle >= PI && fdf->cam.angle < PI + (PI / 2))
		render_fdf_down(fdf);
	else if (fdf->cam.angle >= PI + (PI / 2))
		render_fdf_left(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win_ptr, fdf->img.mlx_img, 0, 0);
	return (0);
}
