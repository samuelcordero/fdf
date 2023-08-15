/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:09:41 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/15 16:22:05 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"



static void	img_pix_put(t_img *img, int x, int y, int color)
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

static int interpolate_color(t_point a, t_point b, float t)
{
	int		pr;
	int		pb;
	int		pg;

    pr = (int)(a.color >> 16 & 0xFF) * (1 - t) + (int)(b.color >> 16 & 0xFF) * t;
    pg = (int)(a.color >> 8 & 0xFF) * (1 - t) + (int)(b.color >> 8 & 0xFF) * t;
    pb = (int)(a.color & 0xFF) * (1 - t) + (int)(b.color & 0xFF) * t;
    return ((pr << 16) | (pg << 8) | pb);
}

static void	render_high_steep_wu_line(t_img *img, t_point *a, t_point *b)
{
	float	dx;
	float	dy;
	float 	gradient;

	dx = b->proy_x - a->proy_x;
	dy = b->proy_y - a->proy_y;
	gradient = dy / dx;
	if (dx == 0.0)
		gradient = 1.0;
	
}

static void	render_low_steep_wu_line(t_img *img, t_point *a, t_point *b)
{

}

static void	render_wu_line(t_img *img, t_point a, t_point b)
{
	t_point *origin;
	t_point *end;

	origin = &a;
	end = &b;
	if (a.proy_x > b.proy_x)
	{
		origin = &b;
		end = &a;
	}
	if (abs(b.proy_y - a.proy_y) > abs(b.proy_x - a.proy_x))
		render_high_steep_wu_line(img, origin, end);
	else
		render_low_steep_wu_line(img, origin, end);
}

static void render_line(t_img *img, t_point a, t_point b)
{
    int x0 = (int)a.proy_x;
    int y0 = (int)a.proy_y;
    int x1 = (int)b.proy_x;
    int y1 = (int)b.proy_y;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;
	//ft_printf("putting line from %i, %i to %i, %i\n", x0, y0, x1, y1);	
	//sleep(2);
    while ((x0 != x1 && y0 != y1) && (x0 - sx != x1 && y0 - sy != y1)) {
		//ft_printf("putting pixel %i, %i\n", x0, y0);	
        float t = sqrtf((x0 - a.proy_x) * (x0 - a.proy_x) + (y0 - a.proy_y) * (y0 - a.proy_y)) /
                  sqrtf((b.proy_x - a.proy_x) * (b.proy_x - a.proy_x) + (b.proy_y - a.proy_y) * (b.proy_y - a.proy_y));
		int pixel_color = interpolate_color(a, b, t);
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
			if (j + 1 < fdf->map->height)
				render_line(&fdf->img, fdf->map->arr[j][i], fdf->map->arr[j + 1][i]);
			if (i + 1 < fdf->map->width)
				render_line(&fdf->img, fdf->map->arr[j][i], fdf->map->arr[j][i + 1]);
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
	//sleep(1);
	//printf("Angle: %f\n", angle);
    return (0);
}

/* 
static int interpolate_color(t_point a, t_point b, float t)
{
	int		pr;
	int		pb;
	int		pg;

    pr = (int)(a.color >> 16 & 0xFF) * (1 - t) + (int)(b.color >> 16 & 0xFF) * t;
    pg = (int)(a.color >> 8 & 0xFF) * (1 - t) + (int)(b.color >> 8 & 0xFF) * t;
    pb = (int)(a.color & 0xFF) * (1 - t) + (int)(b.color & 0xFF) * t;
    return ((pr << 16) | (pg << 8) | pb);
}

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
		int pixel_color = interpolate_color(a, b, t);
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
} 

static int interpolate_color(t_point a, t_point b, float total, float remaining)
{
	int		pr;
	int		pb;
	int		pg;
	float	t;

	t = remaining / total;
    pr = (int)(a.color >> 16 & 0xFF) * t + (int)(b.color >> 16 & 0xFF) * (1 - t);
    pg = (int)(a.color >> 8 & 0xFF) * t + (int)(b.color >> 8 & 0xFF) * (1 - t);
    pb = (int)(a.color & 0xFF) * t + (int)(b.color & 0xFF) * (1 - t);
    return ((pr << 16) | (pg << 8) | pb);
}

static void render_line(t_img *img, t_point a, t_point b)
{
	int		color;
	int		total_pixels;
	double deltaX = b.proy_x - a.proy_x; // 10
	double deltaY = b.proy_y - a.proy_y; // 0
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
	double pixelX = a.proy_x;
	double pixelY = a.proy_y;
	total_pixels = pixels;
	while (pixels)
	{
		color = interpolate_color(a, b, total_pixels, pixels);
   		img_pix_put(img, (int) pixelX, (int) pixelY, color);
    	pixelX += deltaX;
    	pixelY += deltaY;
    	--pixels;
	}
}
*/