/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:07:46 by sacorder          #+#    #+#             */
/*   Updated: 2023/06/20 13:20:29 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef struct s_camera{
	double alpha;
	double beta;
	double gamma;
	double zoom;
} t_camera;

typedef struct s_point{
	int x;
	int y;
	int z;
	int color;
} t_point;

typedef struct s_segment{
	t_point a;
	t_point b;
} t_segment;

typedef struct s_map{
	t_point **arr;
	int width;
	int height;
	int max_z;
	int min_z;
} t_map;

typedef struct s_fdf{
	t_camera cam;
	t_map map;
	int **img;
	int **processed_img;
} t_fdf;

t_point	ft_rotate_x(t_point point, double angle);
t_point	ft_rotate_y(t_point point, double angle);
t_point	ft_rotate_z(t_point point, double angle);
t_point ft_project_iso(t_point point);

#endif