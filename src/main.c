/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:20:41 by sacorder          #+#    #+#             */
/*   Updated: 2023/06/28 17:43:19 by sacorder         ###   ########.fr       */
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
			//apply rotation form angles in camera
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
	fdf.cam.alpha1 = 0;
	fdf.cam.alpha2 = 0;
	fdf.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Campo de hierro", 1);
	if (!fdf.mlx)
		return (1);
	fdf.img = mlx_new_image(fdf.mlx, WIN_WIDTH, WIN_HEIGHT);
	//ft_transform(&fdf);
	//draw map in image
	//draw menu
	mlx_key_hook(fdf.mlx, &keyboard_hook, (void *)&fdf);
	mlx_mouse_hook(fdf.mlx, &mouse_hook, (void *)&fdf);
	mlx_loop(fdf.mlx);
	return (0);
}