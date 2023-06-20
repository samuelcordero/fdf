/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:09:41 by sacorder          #+#    #+#             */
/*   Updated: 2023/06/20 13:39:44 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	drawsegment(void *mlx, void *mlxwin, t_segment seg, int color)
{
	double deltaX = seg.b.x - seg.a.x; // 10
	double deltaY = seg.b.y - seg.a.y; // 0
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
	double pixelX = seg.a.x;
	double pixelY = seg.b.x;
	while (pixels)
	{
   		mlx_pixel_put(mlx, mlxwin, pixelX, pixelY, color);
    	pixelX += deltaX;
    	pixelY += deltaY;
    	--pixels;
	}
}

void	ft_putimg(void *mlx, void *win, int **img)
{
	void *image = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	int pixel_bits;
	int line_bytes;
	int color;
	int endian;
	char *buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);

	for(int y = 0; y < WIN_HEIGHT; ++y)
		for(int x = 0; x < WIN_WIDTH; ++x)
		{
			color = img[y][x];
			if (pixel_bits != 32)
				color = mlx_get_color_value(mlx, color);
			int pixel = (y * line_bytes) + (x * 4);

			if (endian == 1)        // Most significant (Alpha) byte first
			{
				buffer[pixel + 0] = (color >> 24);
				buffer[pixel + 1] = (color >> 16) & 0xFF;
				buffer[pixel + 2] = (color >> 8) & 0xFF;
				buffer[pixel + 3] = (color) & 0xFF;
			}
    		else if (endian == 0)   // Least significant (Blue) byte first
			{
        		buffer[pixel + 0] = (color) & 0xFF;
				buffer[pixel + 1] = (color >> 8) & 0xFF;
				buffer[pixel + 2] = (color >> 16) & 0xFF;
        		buffer[pixel + 3] = (color >> 24);
		    }
		}
	mlx_put_image_to_window(mlx, win, image, 0, 0);
}
