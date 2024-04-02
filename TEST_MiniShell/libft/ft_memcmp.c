/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:40:15 by smortemo          #+#    #+#             */
/*   Updated: 2023/11/09 17:28:53 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	const char		*r1;
	const char		*r2;

	r1 = s1;
	r2 = s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (r1[i] != r2[i])
			return ((unsigned const char)r1[i] - (unsigned const char)r2[i]);
		i++;
	}
	return (0);
}
