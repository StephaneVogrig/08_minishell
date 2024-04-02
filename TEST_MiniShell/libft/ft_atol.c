/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:15:56 by smortemo          #+#    #+#             */
/*   Updated: 2024/02/13 19:01:44 by smortemo         ###   ########.fr       */
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
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign = -1;
		i++;
	}
	if (ft_isdigit(str[i]) == 0)
	{
		write(1, "error!", 6);
		return (0);
	}
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - 48);
	num = sign * num;
	if (num > 2147483647 || num < -2147483648)
		return (0);
	return (num);
}
