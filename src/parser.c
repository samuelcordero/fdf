/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:24:41 by sacorder          #+#    #+#             */
/*   Updated: 2023/06/23 15:16:42 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	ft_free_array(void **array) {
	int pos = 0;

	if (!array)
		exit(-1);
	while (array[pos]) {
		free(array[pos]);
		array[pos] = NULL;
		pos++;
	}
	free(array);
}

static t_point ft_str2point(int x, int y, char *str)
{
	t_point	this;
	char	*splited;

	splited = ft_split(str, ",")
	if (!splited)
		return (NULL);
	this.x = x;
	this.y = y;
	this.z = ft_atoi(split[0]);
	if (splited[1])
		this.color = ft_atoibase(splited[1]);
	ft_free_array(splited);
	return (this);
}

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

static void		ft_str2maprow(t_map *map, char *str, int row)
{
	int	pos;
	char **splited;

	pos = -1;
	max = 0;
	if (!str)
		return (NULL);
	splited = ft_split(str, " ");
	if (!splited)
		return (NULL);
	if (!row)
		map->width = ft_array_len(splited);
	else if (map->width != ft_array_len(splited))
		ft_printf("weird");
	map->arr[row] = malloc(sizeof(int) * (map->width));
	while (++pos < map->width)
	{
		map->arr[row][pos] = ft_str2point(pos, row, splited[pos]);
		if (map->max_z < map->arr[row][pos]->z)
			map->max_z = map->arr[row][pos]->z;
		if (map->min_z > map->arr[row][pos]->z)
			map->min_z = map->arr[row][pos]->z;
	}
	ft_free_array(splited);
}

static int **ft_realloc_map(t_point **arr, int *row_size)
{
	int	new_size;
	t_point	**res;
	int	pos;

	if (*row_size >= 46340)
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
	int		tmpmax;

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
		//buffer to map row and pass & setting of max and min z each row
		free(buffer);
		row++;
		buffer = get_next_line(fd);
		if (row == res->height && buffer)
			res->arr = ft_realloc_map(res->arr, &res->height);
	}
	res->arr[row] = NULL;
	res->height = row;
	return (res);
}
