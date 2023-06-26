/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:36:46 by sacorder          #+#    #+#             */
/*   Updated: 2023/06/27 00:38:52 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void ft_rotate_x(t_point *point, double angle)
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
}

t_point ft_project_iso(t_point point)
{
	t_point projected;

	projected.x = point.x*10;
	projected.y = (point.y * 10) + (point.z * 10);
	projected.color = point.color;
	return (projected);
}