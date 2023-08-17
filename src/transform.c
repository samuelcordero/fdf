/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:36:46 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/17 18:05:18 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	ft_rotate_point(t_point *pnt, double ang, int h_wdth, int h_hght)
{
	pnt->proy_x = (cos(ang) * (pnt->x - h_wdth))
		- (sin(ang) * (pnt->y - h_hght));
	pnt->proy_y = (sin(ang) * (pnt->x - h_wdth))
		+ (cos(ang) * (pnt->y - h_hght));
}

static void	ft_rotate_map(t_map *map, double angle)
{
	int	i;
	int	j;
	int	half_height;
	int	half_width;

	half_height = map->height / 2;
	half_width = map->width / 2;
	j = -1;
	while (++j < map->height)
	{
		i = -1;
		while (++i < map->width)
			ft_rotate_point(&map->arr[j][i], angle, half_width, half_height);
	}
}

static void	proj_pnt_iso(t_point *pnt, double t_sze, double v_sze, t_cam *cam)
{
	double	prev_x;
	int		h_wdth;
	int		h_hght;

	prev_x = pnt->proy_x;
	h_wdth = WIN_WIDTH / 2;
	h_hght = WIN_HEIGHT / 2;
	pnt->proy_x = cam->x + ((prev_x - pnt->proy_y) * (t_sze)) + h_wdth;
	pnt->proy_y = cam->y + h_hght + (((prev_x + pnt->proy_y)
				* (t_sze) - (pnt->z * v_sze)) / 2);
}

void	ft_project_iso(t_map *map, t_cam *cam)
{
	int		i;
	int		j;
	double	height_factor;

	j = -1;
	ft_rotate_map(map, cam->angle);
	if (fabs(map->min_z) > fabs(map->max_z))
		height_factor = 1 / fabs(map->min_z);
	else
		height_factor = 1 / fabs(map->max_z);
	height_factor *= map->h_tile_size;
	if (isinf(height_factor) || height_factor < 10)
		height_factor = map->h_tile_size;
	while (++j < map->height)
	{
		i = -1;
		while (++i < map->width)
			proj_pnt_iso(&map->arr[j][i],
				map->h_tile_size, height_factor, cam);
	}
}

/* 
void ft_rotate_y(t_point *point, double angle)
{
	int prev_x;
	int	prev_z;
	
	prev_x = point->x;
	prev_z = point->z;
	point->x = (cos(angle) * prev_x) + (sin(angle) * prev_z);
	point->z = (cos(angle) * prev_z) - (sin(angle) * prev_x);
}

void ft_rotate_z(t_point *point, double angle)
{
	int prev_x;
	int	prev_y;
	
	prev_x = point->x;
	prev_y = point->y;
	point->x = (cos(angle) * prev_x) - (sin(angle) * prev_y);
	point->y = (sin(angle) * prev_x) + (cos(angle) * prev_y);
} */
