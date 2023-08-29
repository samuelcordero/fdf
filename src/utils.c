/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:29:58 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/29 14:52:18 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		exit(-1);
	while (array[i] != NULL)
	{
		free(array[i]);
		++i;
	}
	free(array);
}

static int	ft_get_int_from_base(char c, char *base)
{
	int		i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int		i;
	int		result;
	int		base_divider;
	int		digit;

	base_divider = (int) ft_strlen(base);
	result = 0;
	i = 0;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '0')
		++i;
	if (str[i] == 'x')
		++i;
	while (str[i] && !ft_isspace(str[i]))
	{
		result *= base_divider;
		digit = ft_get_int_from_base(str[i], base);
		if (digit < 0)
			return (-1);
		result += digit;
		i++;
	}
	return (result);
}

//returns an int representing a color between a.color and b.color, 
//based on a displacement [0,1] calculated rom  distance from a to b
// and brightness [0,1]
int	intrpol_col(int acol, int bcol, double t, double brght)
{
	int	pr;
	int	pg;
	int	pb;

	pr = (int)(((acol >> 16 & 0xFF) * t
				+ (bcol >> 16 & 0xFF) * (1 - t)) * brght);
	pg = (int)(((acol >> 8 & 0xFF) * t
				+ (bcol >> 8 & 0xFF) * (1 - t)) * brght);
	pb = (int)(((acol & 0xFF) * t
				+ (bcol & 0xFF) * (1 - t)) * brght);
	return ((pr << 16) | (pg << 8) | pb);
}

t_point	**ft_realloc_maparr(t_point **arr, int *row_size)
{
	int		new_size;
	t_point	**res;
	int		pos;

	if (*row_size >= (2147483647 / 2))
		new_size = 2147483647 - 1;
	else
		new_size = *row_size * 2;
	pos = -1;
	res = malloc(sizeof(t_point *) * (new_size + 1));
	if (!res)
		return (free(arr), NULL);
	while (++pos < *row_size)
		res[pos] = arr[pos];
	free(arr);
	*row_size = new_size;
	res[new_size] = NULL;
	return (res);
}
