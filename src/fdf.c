/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:07:44 by sacorder          #+#    #+#             */
/*   Updated: 2023/05/24 16:39:32 by sacorder         ###   ########.fr       */
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

int	*ft_carr_to_iarr(char **carr)
{
	int	*iarr;
	int	len;
	int	pos;

	pos = -1;
	if (!carr)
		return (NULL);
	len = ft_array_len(carr);
	iarr = malloc(sizeof(int) * (len + 1));
	while (++pos < len)
		iarr[pos] = ft_atoi(carr[pos]);
	iarr[pos] = INT_MIN;
	return (iarr);
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

int	**parse_map(char *file)
{
	int		fd;
	int		**res;
	int		row_size;
	int		row;
	char	*buffer;
	char	**splitted_buffer;

	row_size = 8;
	row = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd("Couldn't open specified file", 2), NULL); 
	res = malloc(sizeof(int *) * (row_size + 1));
	res[row_size] = NULL;
	buffer = get_next_line(fd);
	while (buffer)
	{
		splitted_buffer = ft_split(buffer, ' ');
		res[row] = ft_carr_to_iarr(splitted_buffer);
		ft_free_array((void **) splitted_buffer);
		free(buffer);
		row++;
		buffer = get_next_line(fd);
		if (row == row_size && buffer)
			res = ft_realloc_iarr(res, &row_size);
	}
	res[row] = NULL;
	close(fd);
	return (res);
}

void	ft_printmap(int **map)
{
	int x;
	int	y;

	x = -1;
	y = x;
	while(map[++y])
	{
		while (map[y][++x] != INT_MIN)
		{
			ft_putnbr_fd(map[y][x], 1);
			ft_putstr_fd("  ", 1);
		}
		ft_putchar_fd('\n', 1);
		x = -1;
	}
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	int		**map;

	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, 400, 400, "Test window!");
	if (argc != 2)
		return(ft_putendl_fd("Wrong args. Usage: ./fdf mapfile.fdf", 2), 1);
	map = parse_map(argv[1]);
	if (!map)
		return(ft_putendl_fd("Couldn't load map", 2), 1);
	ft_printmap(map);
	/* drawline(mlx, win, 400, 400, 0, 0, 0xFF0000);
	while(1)
		ft_putendl_fd("ok", 1); */
	return (0); 
}