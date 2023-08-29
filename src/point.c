/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacorder <sacorder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 00:00:30 by sacorder          #+#    #+#             */
/*   Updated: 2023/08/30 00:02:27 by sacorder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

t_point	ft_str2point(char *substr, int len)
{
	t_point	this;
	int		i;

	i = 0;
	this.z = ft_atoi(substr);
	while ((ft_isdigit(substr[i]) || substr[i] == '-'
			|| substr[i] == '+') && i < len)
		++i;
	while (substr[i] == ',' && i < len)
		++i;
	if (substr[i] && !ft_isspace(substr[i]) && i < len)
	{
		this.color = ft_atoi_base(&substr[i], "0123456789abcdef");
		if (this.color == -1)
			this.color = ft_atoi_base(&substr[i], "0123456789ABCDEF");
	}
	else
		this.color = -1;
	return (this);
}
