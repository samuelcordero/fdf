/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:36:46 by sacorder          #+#    #+#             */
/*   Updated: 2023/06/20 13:20:27 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

t_point ft_rotate_x(point_t point, double angle)
{
	t_point res;

	res.x = point.x;
	res.y = cos(angle) * point.y - sin(angle) * point.z;
	res.z = sin(angle) * point.y + con(angle) * point.z;
	res.color = point.color;
	return (res):
}

t_point ft_rotate_y(point_t point, double angle)
{
	t_point res;

	res.x = cos(angle) * point.x + sin(angle) * point.z;
	res.y = point.y;
	res.z = con(angle) * point.z - sin(angle) * point.x;
	res.color = point.color;
	return (res):
}

t_point ft_rotate_z(point_t point, double angle)
{
	t_point res;

	res.x = cos(angle) * point.x - sin(angle) * point.y;
	res.y = sin(angle) * point.x + con(angle) * point.y;
	res.z = point.z;
	res.color = point.color;
	return (res):
}

t_point ft_project_iso(t_point point)
{
	t_point projected;

	projected.x = point.x;
	projected.y = point.z;
	projected.z = 0;
	projected.color = point.color;
	return (projected);
}