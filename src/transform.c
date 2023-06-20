/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:36:46 by sacorder          #+#    #+#             */
/*   Updated: 2023/06/20 12:25:01 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

point_t ft_rotate_x(point_t point, double angle)
{
	point_t res;

	res.x = point.x;
	res.y = cos(angle) * point.y - sin(angle) * point.z;
	res.z = sin(angle) * point.y + con(angle) * point.z;
	return (res):
}

point_t ft_rotate_y(point_t point, double angle)
{
	point_t res;

	res.x = cos(angle) * point.x + sin(angle) * point.z;
	res.y = point.y;
	res.z = con(angle) * point.z - sin(angle) * point.x;
	return (res):
}

point_t ft_rotate_z(point_t point, double angle)
{
	point_t res;

	res.x = cos(angle) * point.x - sin(angle) * point.y;
	res.y = sin(angle) * point.x + con(angle) * point.y;
	res.z = point.z;
	return (res):
}

point_t ft_project_iso(ft_point point)
{
	t_point projected;

	projected.x = 
	projected.y = 
	projected.z = 0;
	return (projected);
}