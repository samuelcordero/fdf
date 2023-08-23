/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:51:11 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/17 18:45:29 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

double	fpart(float x)
{
	return (x - floor(x));
}

double	rfpart(float x)
{
	return (1 - fpart(x));
}

/* doesnt work as intended, should calculate intermediate points also
int	both_invisible(t_point *a, t_point *b)
{
	if ((a->proy_x < 0 || a->proy_x >= WIN_WIDTH
			|| a->proy_y < 0 || a->proy_y >= WIN_HEIGHT)
		&& (b->proy_x < 0 || b->proy_x >= WIN_WIDTH
			|| b->proy_y < 0 || b->proy_y >= WIN_HEIGHT))
		return (1);
	return (0);
}*/
