/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousehooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:09:43 by sacorder          #+#    #+#             */
/*   Updated: 2023/06/28 17:42:46 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	mouse_hook(int button, int x, int y, void *param);
{
	t_fdf	*fdf;

	fdf = param;

	if (button == WHEEL_UP)
	{
		fdf->cam.zoom += 0.1;
		//redraw
	}
	else if (button == WHEEL_DOWN)
	{
		fdf->cam.zoom -= 0.1;
		//redraw
	}
}
