/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:07:46 by sacorder          #+#    #+#             */
/*   Updated: 2023/07/15 14:37:18 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_WIDTH 1280
# define WIN_HEIGHT 960

//key definitions

# define HELP_KEY 72
# define ROTATE_UP_KEY 73
# define ROTATE_LEFT_KEY 74
# define ROTATE_DOWN_KEY 75
# define ROTATE_RIGHT_KEY 76

# define WHEEL_UP 3
# define WHEEL_DOWN 4

# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef struct s_camera{
	double	angle;
	int		x;
	int		y;
} t_camera;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
} t_img;

typedef struct s_point{
	float x;
	float y;
	float z;
	int color;
} t_point;


typedef struct s_map{
	t_point **arr;
	int width;
	int height;
	float max_z;
	float min_z;
	float h_tile_size;
} t_map;

typedef struct s_fdf{
	t_map	*map;
	void	*mlx;
	void	*win_ptr;
	t_img	img;
	//t_cam	cam;
} t_fdf;

//draw.c

int		render(t_fdf *fdf);

//project.c

void	ft_project_iso(t_map *map);
void	ft_rotate_map(t_map *map, float angle);

//utils.c

void	ft_free_array(char **array);
int		ft_atoi_base(char *str, char *base);

//parser.c

t_map	*parse_map(int fd);

void	mouse_hook(int button, int x, int y, void *param);
void	keyboard_hook(int keycode, void *param);
#endif