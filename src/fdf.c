/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:07:44 by sacorder          #+#    #+#             */
/*   Updated: 2023/05/24 17:55:19 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	ft_sqrt(float number)
{
	long	i;
	float	x2;
	float	y;

	x2 = number * 0.5F;
	y  = number;
	i  = * (long *) &y;
	i  = 0x5f3759df - ( i >> 1 );
	y  = * (float *) &i;
	y  = y * ( 1.5F - ( x2 * y * y ) );
	return 1/y;
}

void	drawline(void *mlx, void *mlxwin, int x0, int y0, int x1, int y1, int color)
{
	double deltaX = x1 - x0; // 10
	double deltaY = y1 - y0; // 0
	int pixels = ft_sqrt((deltaX * deltaX) + (deltaY * deltaY));

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

void	ft_carr_to_iarr(t_fdfmap *map, char **carr, int row)
{
	int	pos;

	pos = -1;
	if (!carr)
		return (NULL);
	if (!row)
		map->width = ft_array_len(carr);
	else if (map->width != ft_array_len(carr))
		exit(1);
	map->arr[row] = malloc(sizeof(int) * (map->width));
	while (++pos < map->width)
		map->arr[row][pos] = ft_atoi(carr[pos]);
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

	res = malloc(sizeof(t_fdfmap));
	res->height = 8;
	row = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(1);
		//return (ft_putendl_fd("Couldn't open specified file", 2), NULL); 
	res->arr = malloc(sizeof(int *) * (res->height + 1));
	res->arr[res->height] = NULL;
	buffer = get_next_line(fd);
	while (buffer)
	{
		splitted_buffer = ft_split(buffer, ' ');
		ft_carr_to_iarr(res, splitted_buffer, row);
		ft_free_array((void **) splitted_buffer);
		free(buffer);
		row++;
		buffer = get_next_line(fd);
		if (row == res->height && buffer)
			res->arr = ft_realloc_iarr(res->arr, &res->height);
	}
	res->arr[row] = NULL;
	close(fd);
	return (res);
}

void	ft_printmap(t_fdfmap map)
{
	int x;
	int	y;

	x = -1;
	y = x;
	while(map.arr[++y])
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

int	main(int argc, char **argv)
{
	void		*mlx;
	void		*win;
	t_fdfmap	*map;

	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, 400, 400, "Test window!");
	if (argc != 2)
		return(ft_putendl_fd("Wrong args. Usage: ./fdf mapfile.fdf", 2), 1);
	map = parse_map(argv[1]);
	ft_printf("height: %i, width: %i\n", map->height, map->width);
	if (!map->arr)
		return(ft_putendl_fd("Couldn't load map", 2), 1);
	ft_printmap(*map);
	/* drawline(mlx, win, 400, 400, 0, 0, 0xFF0000);
	while(1)
		ft_putendl_fd("ok", 1); */
	return (0); 
}