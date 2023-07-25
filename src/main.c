/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:20:41 by sacorder          #+#    #+#             */
/*   Updated: 2023/07/25 23:38:39 by sacorder         ###   ########.fr       */
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

static void	init(t_fdf *fdf)
{
	if (!fdf->mlx)
		exit(1);
	fdf->win_ptr = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "fdf");
	if (fdf->win_ptr == NULL)
		exit(1);
	fdf->img.mlx_img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img.mlx_img)
		exit(1);
	fdf->img.addr = mlx_get_data_addr(fdf->img.mlx_img, &fdf->img.bpp, &fdf->img.line_len, &fdf->img.endian);
	if (!fdf->img.addr)
		exit(1);
}

int	main(int argc, char **argv)
{
	t_fdf fdf;
	int fd;

	fdf.mlx = mlx_init();
	init(&fdf);
	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY, 0644);
	if (fd < 0)
		return (1);
	fdf.map = parse_map(fd);
	mlx_loop_hook(fdf.mlx, &render, &fdf);
	mlx_hook(fdf.win_ptr, 17, 0, &hook_exit, &fdf);
	mlx_hook(fdf.win_ptr, 2, 1, &ft_input_hook, &fdf);
	mlx_loop(fdf.mlx);
	free(fdf.mlx);
	return (0);
}
