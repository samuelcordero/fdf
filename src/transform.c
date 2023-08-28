/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:36:46 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/28 13:40:55 by sacorder         ###   ########.fr       */
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

static void	ft_rotate_map(t_map *map, double *angle)
{
	int	i;
	int	j;
	int	half_height;
	int	half_width;

	half_height = map->height / 2;
	half_width = map->width / 2;
	j = -1;
	if (*angle >= PI2)
		*angle -= PI2;
	else if (*angle < 0)
		*angle += PI2;
	while (++j < map->height)
	{
		i = -1;
		while (++i < map->width)
			ft_rotate_point(&map->arr[j][i], *angle, half_width, half_height);
	}
}

static void	proj_pnt(t_point *pnt, double t_sze, double v_sze, t_cam *cam)
{
	double	prev_x;
	int		h_wdth;
	int		h_hght;

	prev_x = pnt->proy_x;
	h_wdth = WIN_WIDTH / 2;
	h_hght = WIN_HEIGHT / 2;
	if (cam->mode)
	{
		pnt->proy_x = cam->x + ((prev_x - pnt->proy_y) * (t_sze)) + h_wdth;
		pnt->proy_y = cam->y + h_hght + (((prev_x + pnt->proy_y)
					* (t_sze) - (pnt->z * v_sze)) * 0.5);
	}
	else
	{
		pnt->proy_x = cam->x + ((prev_x - pnt->proy_y)
				* (t_sze)) + h_wdth + (pnt->z * v_sze * 0.25);
		pnt->proy_y = cam->y + h_hght + ((prev_x + pnt->proy_y)
				* t_sze) - (pnt->z * v_sze * 0.25);
	}
}

void	ft_project(t_map *map, t_cam *cam)
{
	int		i;
	int		j;

	j = -1;
	ft_rotate_map(map, &(cam->angle));
	while (++j < map->height)
	{
		i = -1;
		while (++i < map->width)
			proj_pnt(&map->arr[j][i],
				map->h_tile_size, map->h_tile_size * cam->v_factor, cam);
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
