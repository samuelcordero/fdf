/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:24:41 by sacorder          #+#    #+#             */
/*   Updated: 2023/07/15 14:58:40 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	ft_array_len(char **arr)
{
	int counter;

	counter = 0;
	if (!arr)
		return (counter);
	while (arr[counter])
		++counter;
	return (counter);
}

static t_point ft_str2point(int x, int y, char *str)
{
	t_point	this;
	char	**splited;
	int		color;

	splited = ft_split(str, ',');
	this.z = 0;
	this.x = x;
	this.y = y;
	if (splited)
		this.z = ft_atoi(splited[0]);
	this.color = 0xFFFFFF;
	if (splited[1])
	{
		color = ft_atoi_base(splited[1], "0123456789ABCDEF");
		if (color == -1)
			this.color = ft_atoi_base(splited[1], "0123456789abcdef");
		else
			this.color = color;
	}
	ft_free_array(splited);
	return (this);
}

static void		ft_str2maprow(t_map *map, char *str, int row)
{
	int	pos;
	char **splited;

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

static t_point **ft_realloc_maparr(t_point **arr, int *row_size)
{
	int	new_size;
	t_point	**res;
	int	pos;

	if (*row_size >= 2147483647/2)
		new_size = 2147483647 - 1;
	else
		new_size = *row_size * 2;
	pos = -1;
	res = malloc(sizeof(t_point *) * (new_size + 1));
	if (!res)
		return(NULL);
	while (++pos < *row_size)
		res[pos] = arr[pos];
	free(arr);
	*row_size = new_size;
	res[new_size] = NULL;
	return (res);
}

t_map	*parse_map(int fd)
{
	t_map	*res;
	int		row;
	char	*buffer;

	if (fd < 0)
		return (NULL);
	res = malloc(sizeof(t_map *));
	res->height = 8;
	res->min_z = 0;
	res->max_z = 0;
	row = 0;
	res->arr = malloc(sizeof(t_point *) * (res->height + 1));
	res->arr[res->height] = NULL;
	buffer = get_next_line(fd);
	while (buffer)
	{
		ft_str2maprow(res, buffer, row);
		free(buffer);
		row++;
		buffer = get_next_line(fd);
		if (row == res->height && buffer)
			res->arr = ft_realloc_maparr(res->arr, &res->height);
	}
	res->arr[row] = NULL;
	res->height = row;
	if ((float) WIN_HEIGHT / (float) res->height > (float) WIN_WIDTH / (float) res->width)
		res->h_tile_size =  0.5 * (float) (WIN_WIDTH - 60) / (float) res->width;
	else
		res->h_tile_size = 0.8 * (float) (WIN_HEIGHT - 60) / (float) res->height;
	return (res);
}
