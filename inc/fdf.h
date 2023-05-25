/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:07:46 by sacorder          #+#    #+#             */
/*   Updated: 2023/05/25 02:56:41 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_WIDTH 500
# define WIN_HEIGHT 500

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef struct s_fdfap{
	int **arr;
	int	width;
	int	height;
} t_fdfmap;

typedef struct s_segment{
	int x0;
	int x1;
	int y0;
	int y1;
} t_segment;

#endif