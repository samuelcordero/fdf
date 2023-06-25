/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:24:41 by sacorder          #+#    #+#             */
/*   Updated: 2023/06/25 18:48:08 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int		ft_is_in_base(char c, char *base)
{
	int		i;

	i = 0;
	while (base[i] != c)
		i++;
	if (base[i] == '\0')
		return (0);
	else
		return (1);
}

int		ft_get_int_from_base(char c, char *base)
{
	int		i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
		{
			return (i);
		}
		i++;
	}
	return (i);
}

int		ft_check_base(char *base)
{
	int		i;
	int		j;

	i = 0;
	while (base[i])
		i++;
	if (i < 2)
		return (0);
	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+' || base[i] == '\f' ||
				base[i] == '\t' || base[i] == ' ' || base[i] == '\n' ||
				base[i] == '\r' || base[i] == '\v')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		skip_whitespace_minus(char *str, int *ptr_i)
{
	int		minus_count;
	int		i;

	i = 0;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == ' ' ||
			str[i] == '\n' || str[i] == '\r' || str[i] == '\v')
		i++;
	minus_count = 0;
	while (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			minus_count++;
		i++;
	}
	*ptr_i = i;
	return (minus_count);
}

int		ft_atoi_base(char *str, char *base)
{
	int		i;
	int		sign;
	int		result;
	int		base_divider;

	i = 0;
	while (base[i])
		i++;
	base_divider = i;
	result = 0;
	sign = 1;
	if (skip_whitespace_minus(str, &i) % 2)
		sign = -1;
	while (str[i] && ft_is_in_base(str[i], base))
	{
		result *= base_divider;
		result += ft_get_int_from_base(str[i], base);
		i++;
	}
	result *= sign;
	return (result);
}

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
	char	**splited;

	splited = ft_split(str, ',');
	if (!splited)
		return (this);
	this.x = x;
	this.y = y;
	this.z = ft_atoi(splited[0]);
	this.color = 0xFFFFFF;
	if (splited[1])
		this.color = ft_atoi_base(splited[1], "0123456789ABCDF");
	ft_free_array((void **) splited);
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
	if (!str)
		return ;
	splited = ft_split(str, ' ');
	if (!splited)
		return ;
	if (!row)
		map->width = ft_array_len(splited);
	else if (map->width != ft_array_len(splited))
		ft_printf("weird");
	map->arr[row] = malloc(sizeof(int) * (map->width));
	while (++pos < map->width)
	{
		map->arr[row][pos] = ft_str2point(pos, row, splited[pos]);
		if (map->max_z < map->arr[row][pos].z)
			map->max_z = map->arr[row][pos].z;
		if (map->min_z > map->arr[row][pos].z)
			map->min_z = map->arr[row][pos].z;
	}
	ft_free_array((void **) splited);
}

static t_point **ft_realloc_map(t_point **arr, int *row_size)
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
