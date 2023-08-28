/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:24:41 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/28 17:19:01 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static t_point	ft_str2point(int x, int y, char *str)
{
	t_point	this;
	char	**splited;

	splited = ft_split(str, ',');
	this.z = 0;
	this.x = x;
	this.y = y;
	if (splited && splited[0])
		this.z = ft_atoi(splited[0]);
	if (splited[1])
	{
		this.color = ft_atoi_base(splited[1], "0123456789ABCDEF");
		if (this.color == -1)
			this.color = ft_atoi_base(splited[1], "0123456789abcdef");
	}
	else
		this.color = -1;
	return (ft_free_array(splited), this);
}

static void	ft_str2maprow(t_map *map, char *str, int row)
{
	int		pos;
	char	**splited;

	pos = -1;
	if (!str)
		return ;
	splited = ft_split(str, ' ');
	if (!splited)
		return ;
	if (!row)
		map->width = ft_array_len(splited);
	else if (map->width > ft_array_len(splited))
		map->width = ft_array_len(splited);
	map->arr[row] = malloc(sizeof(t_point) * (map->width));
	while (++pos < map->width)
	{
		map->arr[row][pos] = ft_str2point(pos, row, splited[pos]);
		if (map->max_z < map->arr[row][pos].z)
			map->max_z = map->arr[row][pos].z;
		if (map->min_z > map->arr[row][pos].z)
			map->min_z = map->arr[row][pos].z;
	}
	ft_free_array(splited);
}

static t_point	**ft_realloc_maparr(t_point **arr, int *row_size)
{
	int		new_size;
	t_point	**res;
	int		pos;

	if (*row_size >= (2147483647 / 2))
		new_size = 2147483647 - 1;
	else
		new_size = *row_size * 2;
	pos = -1;
	res = malloc(sizeof(t_point *) * (new_size + 1));
	if (!res)
		return (free(arr), NULL);
	while (++pos < *row_size)
		res[pos] = arr[pos];
	free(arr);
	*row_size = new_size;
	res[new_size] = NULL;
	return (res);
}

void	recheck_colors(t_map *map)
{
	int	i;
	int	j;

	j = -1;
	if ((float) WIN_HEIGHT / (float) map->height
		> (float) WIN_WIDTH / (float) map->width)
		map->h_tile_size = 0.7 * (float)(WIN_WIDTH) / (float)map->width;
	else
		map->h_tile_size = 0.7 * (float)(WIN_HEIGHT) / (float)map->height;
	while (++j < map->height)
	{
		i = -1;
		while (++i < map->width)
		{
			if (map->arr[j][i].color == -1)
				map->arr[j][i].color = intrpol_col(0xFF0000, 0x0000FF,
						fabs(map->arr[j][i].z - map->min_z)
						/ fabs (map->max_z - map->min_z), 1);
			if (map->arr[j][i].color <= 0)
				map->arr[j][i].color = 0x880088;
		}
	}
}

static t_map	*init_params(int *row, t_map *res)
{
	res = malloc(sizeof(t_map));
	if (!res)
	{
		ft_putendl_fd("Couldn't allocate map memory :(", 2);
		exit(1);
	}
	res->height = 32;
	res->min_z = (double) INT_MAX;
	res->max_z = (double) INT_MIN;
	*row = 0;
	res->arr = malloc(sizeof(t_point *) * (res->height + 1));
	if (!res->arr)
	{
		ft_putendl_fd("Couldn't allocate map memory :(", 2);
		free(res);
		exit(1);
	}
	return (res);
}

t_map	*parse_map(int fd)
{
	t_map	*res;
	int		row;
	char	*buffer;

	res = NULL;
	res = init_params(&row, res);
	res->arr[res->height] = NULL;
	buffer = get_next_line(fd);
	while (buffer)
	{
		ft_str2maprow(res, buffer, row);
		free(buffer);
		buffer = get_next_line(fd);
		if (++row == res->height && buffer)
		{
			res->arr = ft_realloc_maparr(res->arr, &res->height);
			if (!res->arr)
				return (free(res), NULL);
		}
	}
	return (res->arr[row] = NULL, res->height = row,
		recheck_colors(res), res->og_tile_size = res->h_tile_size, res);
}
