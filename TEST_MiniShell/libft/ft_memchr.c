/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:40:15 by smortemo          #+#    #+#             */
/*   Updated: 2023/11/14 14:15:30 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	const char		*l;	
	unsigned char	*r;

	l = s;
	r = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (r[i] == (unsigned char)c)
		{
			l = &s[i];
			return ((void *)l);
		}
		i++;
	}
	return (NULL);
}
