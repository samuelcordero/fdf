/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:07:44 by sacorder          #+#    #+#             */
/*   Updated: 2023/05/25 21:49:03 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	drawline(void *mlx, void *mlxwin, int x0, int y0, int x1, int y1, int color)
{
	double deltaX = x1 - x0; // 10
	double deltaY = y1 - y0; // 0
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
	double pixelX = x0;
	double pixelY = y0;
	while (pixels)
	{
   		mlx_pixel_put(mlx, mlxwin, pixelX, pixelY, color);
    	pixelX += deltaX;
    	pixelY += deltaY;
    	--pixels;
	}
}

void	drawsegment(void *mlx, void *mlxwin, t_segment seg, int color)
{
	double deltaX = seg.x1 - seg.x0; // 10
	double deltaY = seg.y1 - seg.y0; // 0
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
	double pixelX = seg.x0;
	double pixelY = seg.y0;
	while (pixels)
	{
   		mlx_pixel_put(mlx, mlxwin, pixelX, pixelY, color);
    	pixelX += deltaX;
    	pixelY += deltaY;
    	--pixels;
	}
}

t_segment	*ft_transform_segment(t_segment seg)
{
	t_segment	*res;

	res = malloc(sizeof(t_segment));
	if (!res)
		return (NULL);
	res->x0 = seg.x0 - seg.y0;
	res->y0 = (seg.x0 * 0.5) + (seg.y0 * 0.5);
	res->x1 = seg.x1 - seg.y1;
	res->y1 = (seg.x1 * 0.5) + (seg.y1 * 0.5);
	//ft_printf("original: x0:%i x1:%i y0:%i y1:%i transformed: x0:%i x1:%i y0:%i y1:%i\n", seg.x0,);
	return (res);
}
int	ft_array_len(char **arr)
{
	int counter;

	counter = 0;
	if (!arr)
		return (counter);
	while (arr[counter])
		++counter;
	return (counter);
}

int		ft_carr_to_iarr(t_fdfmap *map, char **carr, int row)
{
	int	pos;
	int	max;

	pos = -1;
	max = 0;
	if (!carr)
		return (NULL);
	if (!row)
		map->width = ft_array_len(carr);
	else if (map->width != ft_array_len(carr))
		ft_printf("weird");
	map->arr[row] = malloc(sizeof(int) * (map->width));
	while (++pos < map->width)
	{
		map->arr[row][pos] = ft_atoi(carr[pos]);
		if (max < abs(map->arr[row][pos]))
			max = abs(map->arr[row][pos]);
	}
	return (max);
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

int **ft_realloc_iarr(int **arr, int *row_size)
{
	int	new_size;
	int	**res;
	int	pos;

	if (*row_size >= 46340)
		new_size = 2147483647 - 1;
	else
		new_size = *row_size * 2;
	pos = -1;
	res = malloc(sizeof(int *) * (new_size + 1));
	if (!res)
		return(NULL);
	while (++pos < *row_size)
		res[pos] = arr[pos];
	free(arr);
	*row_size = new_size;
	res[new_size] = NULL;
	return (res);
}

t_fdfmap	*parse_map(char *file)
{
	t_fdfmap	*res;
	int		fd;
	int		row;
	char	*buffer;
	char	**splitted_buffer;
	int		tmpmax;

	res = malloc(sizeof(t_fdfmap));
	res->height = 8;
	res->max_abs = 0;
	row = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd("Couldn't open specified file", 2), NULL); 
	res->arr = malloc(sizeof(int *) * (res->height + 1));
	res->arr[res->height] = NULL;
	buffer = get_next_line(fd);
	while (buffer)
	{
		splitted_buffer = ft_split(buffer, ' ');
		tmpmax = ft_carr_to_iarr(res, splitted_buffer, row);
		if (tmpmax > res->max_abs)
			res->max_abs = tmpmax;
		ft_free_array((void **) splitted_buffer);
		free(buffer);
		row++;
		buffer = get_next_line(fd);
		if (row == res->height && buffer)
			res->arr = ft_realloc_iarr(res->arr, &res->height);
	}
	res->arr[row] = NULL;
	res->height = row;
	close(fd);
	return (res);
}

void	ft_printmap(t_fdfmap map)
{
	int x;
	int	y;

	x = -1;
	y = x;
	while (++y < map.height)
	{
		while (++x < map.width)
		{
			ft_putnbr_fd(map.arr[y][x], 1);
			ft_putchar_fd(' ', 1);
		}
		ft_putchar_fd('\n', 1);
		x = -1;
	}
}

void	ft_putmap(t_fdfmap map, void *mlx, void *win)
{
	int xp = 10;
	int yp = 10;
	int x = -1;
	int y = -1;
	float delta;
	float zscale;
	t_segment *original;
	t_segment *transformed;

	original = malloc(sizeof(t_segment));
	if ((WIN_WIDTH - (2*xp)) / map.width < (WIN_HEIGHT - (2*yp)) / map.height)
		delta = (WIN_WIDTH - (2*xp)) / map.width;
	else
		delta = (WIN_HEIGHT - (2*yp)) / map.height;
	zscale = delta;
	delta *= 0.6;
	while (zscale * map.max_abs >= WIN_HEIGHT / 2)
		zscale *= 0.9;
	xp = WIN_WIDTH / 2;
	while (++y < map.height)
	{
		while (++x < map.width)
		{
			original->x0 = xp;
			original->y0 = yp;
			original->x1 = xp;
			original->y1 = yp + delta;
			if (y < map.height - 1)
			{
				transformed = ft_transform_segment(*original);
				transformed->y0 -= (map.arr[y][x] * zscale);
				transformed->y1 -= (map.arr[y + 1][x] * zscale);
				drawsegment(mlx, win, *transformed, 0xFFFFFF);
				free(transformed);
			}
			original->x1 = xp + delta;
			original->y1 = yp;
			if (x < map.width - 1)
			{
				transformed = ft_transform_segment(*original);
				transformed->y0 -= (map.arr[y][x] * zscale);
				transformed->y1 -= (map.arr[y][x + 1] * zscale);
				drawsegment(mlx, win, *transformed, 0xFFFFFF);
				free(transformed);
			}
			xp += delta;
		}
		xp = WIN_WIDTH / 2;
		yp += delta;
		x = -1;
	}
}

int	main(int argc, char **argv)
{
	void		*mlx;
	void		*win;
	t_fdfmap	*map;

	if (argc != 2)
		return(ft_putendl_fd("Wrong args. Usage: ./fdf mapfile.fdf", 2), 1);
	map = parse_map(argv[1]);
	if (!map || !map->arr)
		return(ft_putendl_fd("Couldn't load map", 2), 1);
	//ft_printf("height: %i, width: %i\n", map->height, map->width);
	//ft_printmap(*map);
	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, argv[1]);
	ft_putmap(*map, mlx, win);
	while(1)
		sleep(5);
	return (0); 
}