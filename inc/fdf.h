/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:07:46 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/17 17:52:01 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FDF_H
# define FDF_H
# define WIN_WIDTH 1800
# define WIN_HEIGHT 1000

//key definitions
# ifndef MAC_OS
#  define ESCAPE 65307
#  define HELP_KEY 72
#  define ROTATE_LEFT 113
#  define ROTATE_RIGHT 101
#  define MOVE_UP 119
#  define MOVE_DOWN 115
#  define MOVE_LEFT 97
#  define MOVE_RIGHT 100
#  define ZOOM_OUT 120
#  define ZOOM_IN 122
#  define RESET_CAM 114

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
#  define RESET_CAM 114 //CHECK

#  define WHEEL_UP 3
#  define WHEEL_DOWN 4
# endif

# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef struct s_camera
{
	double	angle;
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
	double	x;
	double	y;
	double	z;
	double	proy_x;
	double	proy_y;
	int		color;
} t_point;


typedef struct s_map
{
	t_point **arr;
	int width;
	int height;
	double max_z;
	double min_z;
	double h_tile_size;
	double og_tile_size;
} t_map;

typedef struct s_fdf
{
	t_map	*map;
	void	*mlx;
	void	*win_ptr;
	t_img	img;
	t_cam	cam;
} t_fdf;

typedef struct s_xialinwusup
{
	int		xend;
	int		yend;
	int		xgap;
	int		xpxl1;
	int		xpxl2;
	int		ypxl1;
	int		ypxl2;
	double	intery;
	double	dx;
	double	dy;
	double 	gradient;
	char	steep;
} t_xlsup;

//draw.c

void	img_pix_put(t_img *img, int x, int y, int color);
int		render(t_fdf *fdf);

//project.c

void	ft_project_iso(t_map *map, t_cam *cam);

//utils.c

void	ft_free_array(char **array);
int		ft_atoi_base(char *str, char *base);
int		intrpol_col(int acol, int bcol, double t, double brght);
int		both_invisible(t_point *a, t_point *b);


//parser.c

t_map	*parse_map(int fd);

//hooks.c

int		hook_exit(t_fdf *fdf);
int		ft_input_hook(int keycode, t_fdf *fdf);

//wu_line.c

void	render_wu_line(t_img *img, t_point a, t_point b);

//math_utils.c

double	fpart(float x);
double	rfpart(float x);

#endif