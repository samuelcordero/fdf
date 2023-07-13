/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:09:41 by sacorder          #+#    #+#             */
/*   Updated: 2023/07/13 19:32:32 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

/* 
static void render_line(t_img *img, t_point a, t_point b)
{
    int x0 = (int)a.x;
    int y0 = (int)a.y;
    int x1 = (int)b.x;
    int y1 = (int)b.y;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        float t = sqrtf((x0 - a.x) * (x0 - a.x) + (y0 - a.y) * (y0 - a.y)) /
                  sqrtf((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));

        int pixel_color = 0xFFFFFF;
		//int pixel_color = interpolate_color(a, b, t);
        img_pix_put(img, x0, y0, pixel_color);
        if (2 * err > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (2 * err < dx) {
            err += dx;
            y0 += sy;
        }
    }
}*/

static int interpolate_color(t_point a, t_point b, float total, float remaining)
{
	float t;
	int pr;
	int pb;
	int pg;

	t = remaining / total;
    pr = (int)(a.color >> 16 & 0xFF) * (1 - t) + (int)(b.color >> 16 & 0xFF) * t;
    pg = (int)(a.color >> 8 & 0xFF) * (1 - t) + (int)(b.color >> 8 & 0xFF) * t;
    pb = (int)(a.color & 0xFF) * (1 - t) + (int)(b.color & 0xFF) * t;
    return ((pr << 16) | (pg << 8) | pb);
}

/* static void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
} */

static void	img_pix_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(int *)pixel = color;
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

static void render_line(t_img *img, t_point a, t_point b)
{
	int		color;
	int		total_pixels;
	double deltaX = b.x - a.x; // 10
	double deltaY = b.y - a.y; // 0
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
	double pixelX = a.x;
	double pixelY = b.x;
	total_pixels = pixels;
	while (pixels)
	{
		color = interpolate_color(a, b, total_pixels, pixels);
   		img_pix_put(img, pixelX, pixelY, color);
    	pixelX += deltaX;
    	pixelY += deltaY;
    	--pixels;
	}
}

void	render_fdf(t_fdf *fdf)
{
	t_point a, b;

	a.x = 0;
	a.y = 0;
	a.z = 0;
	a.color = 0x000000;
	b.x = WIN_WIDTH - 1;
	b.y = WIN_HEIGHT - 1;
	b.z = 0;
	b.color = 0xFF0000;
	render_line(&fdf->img, a, b);
}

int	render(t_fdf *fdf)
{
    if (fdf->win_ptr == NULL)
        return (1);
    render_black_background(&fdf->img);
	render_fdf(fdf);
    mlx_put_image_to_window(fdf->mlx, fdf->win_ptr, fdf->img.mlx_img, 0, 0);
    return (0);
}
