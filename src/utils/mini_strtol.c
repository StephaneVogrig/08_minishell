/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_strtol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:58:09 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/23 18:07:23 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

static inline long	overflow(char sign)
{
	if (sign == '+')
		return (LONG_MAX);
	return (LONG_MIN);
}

long	mini_strtol(const char *nptr, char **endptr)
{
	long	value;
	char	sign;

	sign = '+';
	value = 0;
	while (is_blank(*nptr))
		nptr++;
	if ((*nptr == '-' || *nptr == '+') && ft_isdigit(*(nptr + 1)))
		sign = *nptr++;
	while (ft_isdigit(*nptr))
	{
		if (value < 0)
			break ;
		value = value * 10 + *nptr - '0';
		if (value < 0 && (sign == '+' || value > LONG_MIN))
			break ;
		nptr++;
	}
	if (endptr)
		*endptr = (char *)nptr;
	if (value < 0)
		return (overflow(sign));
	if (sign == '-')
		value *= -1;
	return (value);
}
