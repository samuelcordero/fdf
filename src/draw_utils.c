/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:29:44 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/28 13:31:18 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

//from map[0][0] to map[map.height - 1][map.width - 1] 
void	render_fdf_down(t_fdf *fdf)
{
	int	i;
	int	j;

	j = -1;
	while (++j < fdf->map->height)
	{
		i = -1;
		while (++i < fdf->map->width)
		{
			if (j + 1 < fdf->map->height
				&& !both_invisible(&fdf->map->arr[j][i],
				&fdf->map->arr[j + 1][i]))
				render_wu_line(&fdf->img, fdf->map->arr[j][i],
					fdf->map->arr[j + 1][i]);
			if (i + 1 < fdf->map->width
				&& !both_invisible(&fdf->map->arr[j][i],
				&fdf->map->arr[j][i + 1]))
				render_wu_line(&fdf->img, fdf->map->arr[j][i],
					fdf->map->arr[j][i + 1]);
			img_pix_put(&fdf->img, (int)fdf->map->arr[j][i].proy_x,
				(int)fdf->map->arr[j][i].proy_y, fdf->map->arr[j][i].color);
		}
	}
}

//from map[map.height - 1][map.width - 1] to map[0][0]
void	render_fdf_up(t_fdf *fdf)
{
	int	i;
	int	j;

	j = fdf->map->height;
	while (--j >= 0)
	{
		i = fdf->map->width;
		while (--i >= 0)
		{
			if (j - 1 >= 0
				&& !both_invisible(&fdf->map->arr[j][i],
				&fdf->map->arr[j - 1][i]))
				render_wu_line(&fdf->img, fdf->map->arr[j][i],
					fdf->map->arr[j - 1][i]);
			if (i - 1 >= 0
				&& !both_invisible(&fdf->map->arr[j][i],
				&fdf->map->arr[j][i - 1]))
				render_wu_line(&fdf->img, fdf->map->arr[j][i],
					fdf->map->arr[j][i - 1]);
			img_pix_put(&fdf->img, (int)fdf->map->arr[j][i].proy_x,
				(int)fdf->map->arr[j][i].proy_y, fdf->map->arr[j][i].color);
		}
	}
}

//from map[map.height - 1][0] to map[0][map.width - 1] 
void	render_fdf_left(t_fdf *fdf)
{
	int	i;
	int	j;

	i = -1;
	while (++i < fdf->map->width)
	{
		j = fdf->map->height;
		while (--j >= 0)
		{
			if (j - 1 >= 0
				&& !both_invisible(&fdf->map->arr[j][i],
				&fdf->map->arr[j - 1][i]))
				render_wu_line(&fdf->img, fdf->map->arr[j][i],
					fdf->map->arr[j - 1][i]);
			if (i + 1 < fdf->map->width
				&& !both_invisible(&fdf->map->arr[j][i],
				&fdf->map->arr[j][i + 1]))
				render_wu_line(&fdf->img, fdf->map->arr[j][i],
					fdf->map->arr[j][i + 1]);
			img_pix_put(&fdf->img, (int)fdf->map->arr[j][i].proy_x,
				(int)fdf->map->arr[j][i].proy_y, fdf->map->arr[j][i].color);
		}
	}
}

//from map[0][map.width - 1] to map[map.height - 1][0] 
void	render_fdf_right(t_fdf *fdf)
{
	int	i;
	int	j;

	i = fdf->map->width;
	while (--i >= 0)
	{
		j = -1;
		while (++j < fdf->map->height)
		{
			if (j + 1 < fdf->map->height
				&& !both_invisible(&fdf->map->arr[j][i],
				&fdf->map->arr[j + 1][i]))
				render_wu_line(&fdf->img, fdf->map->arr[j][i],
					fdf->map->arr[j + 1][i]);
			if (i - 1 >= 0
				&& !both_invisible(&fdf->map->arr[j][i - 1],
				&fdf->map->arr[j][i]))
				render_wu_line(&fdf->img, fdf->map->arr[j][i - 1],
					fdf->map->arr[j][i]);
			img_pix_put(&fdf->img, (int)fdf->map->arr[j][i].proy_x,
				(int)fdf->map->arr[j][i].proy_y, fdf->map->arr[j][i].color);
		}
	}
}
