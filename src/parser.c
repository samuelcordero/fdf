/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:24:41 by sacorder          #+#    #+#             */
/*   Updated: 2023/06/20 13:22:13 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

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
