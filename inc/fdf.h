/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:07:46 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/15 15:22:13 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_WIDTH 1280
# define WIN_HEIGHT 960

//key definitions
# ifndef MAC_OS
#  define ESCAPE 65307
#  define HELP_KEY 72
#  define ROTATE_LEFT 12
#  define ROTATE_RIGHT 14
#  define MOVE_UP 13
#  define MOVE_DOWN 1
#  define MOVE_LEFT 0
#  define MOVE_RIGHT 2
#  define ZOOM_OUT 7
#  define ZOOM_IN 6

#  define WHEEL_UP 3
#  define WHEEL_DOWN 4
# else
#  define ESCAPE 53
#  define HELP_KEY 72
#  define ROTATE_LEFT 12
#  define ROTATE_RIGHT 14
#  define MOVE_UP 13
#  define MOVE_DOWN 1
#  define MOVE_LEFT 0
#  define MOVE_RIGHT 2
#  define ZOOM_OUT 7
#  define ZOOM_IN 6

#  define WHEEL_UP 3
#  define WHEEL_DOWN 4
# endif

# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef struct s_camera
{
	float	angle;
	int		x;
	int		y;
} t_cam;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
} t_img;

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	float	proy_x;
	float	proy_y;
	int		color;
} t_point;


typedef struct s_map
{
	t_point **arr;
	int width;
	int height;
	float max_z;
	float min_z;
	float h_tile_size;
} t_map;

typedef struct s_fdf
{
	t_map	*map;
	void	*mlx;
	void	*win_ptr;
	t_img	img;
	t_cam	cam;
} t_fdf;

//draw.c

int		render(t_fdf *fdf);

//project.c

void	ft_project_iso(t_map *map, t_cam *cam);

//utils.c

void	ft_free_array(char **array);
int		ft_atoi_base(char *str, char *base);

//parser.c

t_map	*parse_map(int fd);

//hooks.c

int		hook_exit(t_fdf *fdf);
int		ft_input_hook(int keycode, t_fdf *fdf);

#endif