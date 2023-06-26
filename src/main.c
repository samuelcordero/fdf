/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:20:41 by sacorder          #+#    #+#             */
/*   Updated: 2023/06/27 01:13:15 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <stdio.h>

void	ft_printmap(t_map *map)
{
	int	i;
	int	j;

	j = 0;
	while (j < map->height)
	{
		i = 0;
		while (i < map->width)
		{
			printf("x: %f, y: %f, z: %f, color: %i\n", map->arr[j][i].x, map->arr[j][i].y, map->arr[j][i].z, map->arr[j][i].color);
			++i;
		}
		printf("------map width: %i------\n", map->width);
		++j;
	}
	printf("------map max and min:  %f %f------\n", map->max_z, map->min_z);
}

void ft_transform(t_fdf *fdf)
{
	int	i;
	int	j;

	j = 0;
	while (j < fdf->map->height)
	{
		i = 0;
		while (i < fdf->map->width)
		{
			printf("Before rotationx: %f, y: %f, z: %f, color: %i\n", fdf->map->arr[j][i].x, fdf->map->arr[j][i].y, fdf->map->arr[j][i].z, fdf->map->arr[j][i].color);
			ft_rotate_x(&fdf->map->arr[j][i], fdf->cam.alpha);
			ft_rotate_y(&fdf->map->arr[j][i], fdf->cam.beta);
			ft_rotate_z(&fdf->map->arr[j][i], fdf->cam.gamma);
			printf("After rotationx: %f, y: %f, z: %f, color: %i\n", fdf->map->arr[j][i].x, fdf->map->arr[j][i].y, fdf->map->arr[j][i].z, fdf->map->arr[j][i].color);
			++i;
		}
		++j;
	}
}

int	main(int argc, char **argv)
{
	t_fdf fdf;
	int fd;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY, 0644);
	if (fd < 0)
		return (1);
	fdf.map = parse_map(fd);
	ft_printmap(fdf.map);
	fdf.cam.zoom = 1;
	fdf.cam.alpha = 1.6;
	fdf.cam.beta = 1.6;
	fdf.cam.gamma = 1.6;
	ft_transform(&fdf);
	//system("sleep 100");
	return (0);
}