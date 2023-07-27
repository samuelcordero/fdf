/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:29:58 by sacorder          #+#    #+#             */
/*   Updated: 2023/07/15 14:55:40 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		exit(-1);
	while (array[i] != NULL) {
		free(array[i]);
		++i;
	}
	free(array);
}

static int		ft_get_int_from_base(char c, char *base)
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

int		ft_atoi_base(char *str, char *base)
{
	int		i;
	int		result;
	int		base_divider;
	int		digit;

	base_divider = (int) ft_strlen(base);
	result = 0;
	i = 0;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == ' ' ||
			str[i] == '\n' || str[i] == '\r' || str[i] == '\v' ||
			str[i] == '0' || str[i] == 'x')
		i++;
	while (str[i] && str[i] != '\n')
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