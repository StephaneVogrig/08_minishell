/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:15:56 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/21 14:36:03 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atol(const char *str)
{
	long long	i;
	long long	num;
	int			sign;

	sign = 1;
	num = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] == ' ' )
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - 48);
	num = sign * num;
	return (num);
}
