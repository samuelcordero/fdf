/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:36:46 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/15 13:21:33 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

//meter aqui la reconversion de manera que el origen del sistema de referencia sea el entro del mapa, 
//por lo que 0,0  pasa a ser -halfwidth, -half_height y half_width, halfhaeight pasa a ser 0, 0
static void ft_rotate_point(t_point *point, double angle, int half_width, int half_height)
{
	point->proy_x = (cos(angle) * (point->x - half_width)) - (sin(angle) * (point->y - half_height));
	point->proy_y = (sin(angle) * (point->x - half_width)) + (cos(angle) * (point->y - half_height));
}

static void	ft_rotate_map(t_map *map, float angle)
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

static void	ft_project_point_iso(t_point *point, float tile_size, float height_factor)
{
	float	prev_x;
	int		half_width;
	int		half_height;

	prev_x = point->proy_x;
	half_width = WIN_WIDTH / 2;
	half_height = 	WIN_HEIGHT / 2;
	point->proy_x = ((prev_x - point->proy_y) * (tile_size)) + half_width;
	point->proy_y = half_height + (((prev_x + point->proy_y) * (tile_size) - (point->z * height_factor)) / 2);
}

void	ft_project_iso(t_map *map, float angle)
{
	int		i;
	int		j;
	float	height_factor;

	j = -1;
	ft_rotate_map(map, angle);
	if (map->min_z * -1 > map->max_z)
		height_factor = WIN_HEIGHT / map->min_z * -1;
	else
		height_factor = WIN_HEIGHT / map->max_z;
	height_factor /= 2.0;
	if (isinf(height_factor))
		height_factor = 1;
	while (++j < map->height)
	{
		i = -1;
		while (++i < map->width)
			ft_project_point_iso(&map->arr[j][i], map->h_tile_size, height_factor);
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
