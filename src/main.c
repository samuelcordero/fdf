/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:20:41 by sacorder          #+#    #+#             */
/*   Updated: 2023/06/25 19:58:21 by sacorder         ###   ########.fr       */
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
}

int	main(int argc, char **argv)
{
	t_fdf fdf;
	int fd;
	t_map *transformed;

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
	transformed = ft_transform(fdf);

	return (0);
}