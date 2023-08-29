/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:24:41 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/30 00:00:20 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	ft_str2maprow_cons(t_map *map, char *str, int row)
{
	int	pos;
	int	end;
	int	arrpos;

	arrpos = -1;
	end = 0;
	while (++arrpos < map->width)
	{
		pos = end;
		while (ft_isspace(str[pos]))
			++pos;
		end = pos;
		while (!ft_isspace(str[end]) && str[end] != '\n')
			++end;
		map->arr[row][arrpos] = ft_str2point(&str[pos], end - pos);
		if (map->max_z < map->arr[row][arrpos].z)
			map->max_z = map->arr[row][arrpos].z;
		if (map->min_z > map->arr[row][arrpos].z)
			map->min_z = map->arr[row][arrpos].z;
	}
}

static void	ft_str2maprow(t_map *map, char *str, int row)
{
	int	pos;
	int	end;

	pos = 0;
	end = 0;
	if (!str)
		return ;
	while (str[pos] && str[pos] != '\n')
	{
		if (!ft_isspace(str[pos]))
		{
			++end;
			while (!ft_isspace(str[pos]) && str[pos])
				++pos;
		}
		else
			++pos;
	}
	if (!row)
		map->width = end;
	else if (map->width > end)
		map->width = end;
	map->arr[row] = malloc(sizeof(t_point) * (map->width));
	ft_str2maprow_cons(map, str, row);
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
	res->height = 128;
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

/* 
static t_point	ft_str2point(char *str)
{
	t_point	this;
	int		i;

	i = 0;
	this.z = ft_atoi(str);
	while (ft_isspace(str[i]))
		++i;
	while (ft_isdigit(str[i]))
		++i;
	while (str[i] == ',')
		++i;
	if (str[i] && !ft_isspace(str[i]))
	{
		this.color = ft_atoi_base(&str[i], "0123456789abcdef");
		if (this.color == -1)
			this.color = ft_atoi_base(&str[i], "0123456789ABCDEF");
	}
	else
		this.color = -1;
	return (this);
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
		map->arr[row][pos] = ft_str2point(splited[pos]);
		if (map->max_z < map->arr[row][pos].z)
			map->max_z = map->arr[row][pos].z;
		if (map->min_z > map->arr[row][pos].z)
			map->min_z = map->arr[row][pos].z;
	}
	ft_free_array(splited);
} */