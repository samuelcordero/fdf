/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wu_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:35:00 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/24 00:32:12 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	wu_startpnt(t_img *img, t_point *a, t_point *b, t_xlsup *sup)
{
	(void) b;
	sup->xend = round(a->proy_x);
	sup->yend = a->proy_y + sup->gradient * ((double) sup->xend - a->proy_x);
	sup->xgap = rfpart(a->proy_x + 0.5);
	sup->xpxl1 = sup->xend;
	sup->ypxl1 = floor(sup->yend);
	if (sup->steep)
	{
		img_pix_put(img, sup->ypxl1, sup->xpxl1,
			intrpol_col(a->color, b->color, 0, rfpart(sup->yend) * sup->xgap));
		img_pix_put(img, sup->ypxl1 + 1, sup->xpxl1,
			intrpol_col(a->color, b->color, 0, fpart(sup->yend) * sup->xgap));
	}
	else
	{
		img_pix_put(img, sup->xpxl1, sup->ypxl1 + 1,
			intrpol_col(a->color, b->color, 0, rfpart(sup->yend) * sup->xgap));
		img_pix_put(img, sup->xpxl1 + 1, sup->ypxl1 + 1,
			intrpol_col(a->color, b->color, 0, fpart(sup->yend) * sup->xgap));
	}
	sup->intery = sup->yend + sup->gradient;
}

static void	wu_endpnt(t_img *img, t_point *a, t_point *b, t_xlsup *sup)
{
	(void) a;
	sup->xend = round(b->proy_x);
	sup->yend = b->proy_y + sup->gradient * ((double) sup->xend - b->proy_x);
	sup->xgap = fpart(b->proy_x + 0.5);
	sup->xpxl2 = sup->xend;
	sup->ypxl2 = floor(sup->yend);
	if (sup->steep)
	{
		img_pix_put(img, sup->ypxl2, sup->xpxl2,
			intrpol_col(a->color, b->color, 1, rfpart(sup->yend) * sup->xgap));
		img_pix_put(img, sup->ypxl2 + 1, sup->xpxl2,
			intrpol_col(a->color, b->color, 1, fpart(sup->yend) * sup->xgap));
	}
	else
	{
		img_pix_put(img, sup->xpxl2, sup->ypxl2 + 1,
			intrpol_col(a->color, b->color, 1, rfpart(sup->yend) * sup->xgap));
		img_pix_put(img, sup->xpxl2 + 1, sup->ypxl2 + 1,
			intrpol_col(a->color, b->color, 1, fpart(sup->yend) * sup->xgap));
	}
}

static void	render_high_steep_wu_line(t_img *img, t_point *a, t_point *b)
{
	t_xlsup	sup;
	int		x;
	double	t;

	sup.dx = b->proy_x - a->proy_x;
	sup.dy = b->proy_y - a->proy_y;
	sup.gradient = sup.dy / sup.dx;
	if (sup.dx == 0.0)
		sup.gradient = 1.0;
	sup.steep = 1;
	wu_startpnt(img, a, b, &sup);
	wu_endpnt(img, a, b, &sup);
	x = sup.xpxl1;
	while (x < sup.xpxl2 -1)
	{
		t = (double) abs(sup.xpxl2 - x) / (double) abs(sup.xpxl2 - sup.xpxl1);
		img_pix_put(img, floor(sup.intery), x, intrpol_col(a->color, b->color,
				t, rfpart(sup.intery)));
		img_pix_put(img, floor(sup.intery) + 1, x, intrpol_col(a->color,
				b->color, t, fpart(sup.intery)));
		sup.intery = sup.intery + sup.gradient;
		++x;
	}
}

static void	render_low_steep_wu_line(t_img *img, t_point *a, t_point *b)
{
	t_xlsup	sup;
	int		x;
	double	t;

	sup.dx = b->proy_x - a->proy_x;
	sup.dy = b->proy_y - a->proy_y;
	sup.gradient = sup.dy / sup.dx;
	if (sup.dx == 0.0)
		sup.gradient = 1.0;
	sup.steep = 0;
	wu_startpnt(img, a, b, &sup);
	wu_endpnt(img, a, b, &sup);
	x = sup.xpxl1;
	while (x < sup.xpxl2 -1)
	{
		t = (double) abs(sup.xpxl2 - x) / (double) abs(sup.xpxl2 - sup.xpxl1);
		img_pix_put(img, x, floor(sup.intery),
			intrpol_col(a->color, b->color, t, rfpart(sup.intery)));
		img_pix_put(img, x, floor(sup.intery) + 1,
			intrpol_col(a->color, b->color, t, fpart(sup.intery)));
		sup.intery = sup.intery + sup.gradient;
		++x;
	}
}

void	render_wu_line(t_img *img, t_point a, t_point b)
{
	t_point	*origin;
	t_point	*end;
	float	tmp;

	origin = &a;
	end = &b;
	tmp = fabs(b.proy_y - a.proy_y) > fabs(b.proy_x - a.proy_x);
	if (tmp)
	{
		tmp = a.proy_x;
		a.proy_x = a.proy_y;
		a.proy_y = tmp;
		tmp = b.proy_y;
		b.proy_y = b.proy_x;
		b.proy_x = tmp;
	}
	if (a.proy_x > b.proy_x)
	{
		origin = &b;
		end = &a;
	}
	if (tmp)
		render_high_steep_wu_line(img, origin, end);
	else
		render_low_steep_wu_line(img, origin, end);
}
