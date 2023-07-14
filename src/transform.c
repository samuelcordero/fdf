/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:36:46 by sacorder          #+#    #+#             */
/*   Updated: 2023/07/14 14:54:05 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	ft_project_point_iso(t_point *point, float tile_size)
{
	float	prev_x;
	int		half_width;

	prev_x = point->x;
	half_width = WIN_WIDTH / 2;
	point->x = ((prev_x - point->y) * (tile_size)) + half_width;
	point->y = (prev_x + point->y) * (tile_size / 2) + point->z * 10;
}

void	ft_project_iso(t_map *map)
{
	int	i;
	int	j;

	j = -1;
	while (++j < map->height)
	{
		i = -1;
		while (++i < map->width)
			ft_project_point_iso(&map->arr[j][i], map->h_tile_size);
	}
	printf("project done\n");
}

/* void ft_rotate_x(t_point *point, double angle)
{
	int prev_y;
	int	prev_z;
	
	prev_y = point->y;
	prev_z = point->z;
	point->y = (cos(angle) * prev_y) - (sin(angle) * prev_z);
	point->z = (sin(angle) * prev_y) + (cos(angle) * prev_z);
}

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
