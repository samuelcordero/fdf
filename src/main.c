/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:20:41 by sacorder          #+#    #+#             */
/*   Updated: 2023/06/26 02:17:21 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

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
			ft_printf("x: %i, y: %i, z: %i, color: %i\n", map->arr[j][i].x, map->arr[j][i].y, map->arr[j][i].z, map->arr[j][i].color);
			++i;
		}
		ft_printf("------map width: %i------\n", map->width);
		++j;
	}
	ft_printf("------map max and min:  %i %i------\n", map->max_z, map->min_z);
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
	//transformed = ft_transform(fdf);
	system("sleep 100");
	return (0);
}