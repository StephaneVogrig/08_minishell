/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:22:40 by smortemo          #+#    #+#             */
/*   Updated: 2023/11/03 15:36:52 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int			i;
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	i = (int)n - 1;
	if (src < dest)
	{
		while (i >= 0)
		{
			d[i] = s[i];
			i--;
		}
	}
	i = 0;
	if (src > dest)
	{
		while (i < (int)n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
