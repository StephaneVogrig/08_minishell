/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:52:09 by smortemo          #+#    #+#             */
/*   Updated: 2024/01/14 13:31:50 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	const char		*r;

	r = s;
	i = 0;
	while (i < ft_strlen(s))
	{
		if ((unsigned char)s[i] == (unsigned char)c)
		{
			r = &s[i];
			return ((char *)r);
		}
		i++;
	}
	if (c == '\0')
	{
		r = &s[i];
		return ((char *)r);
	}
	return (NULL);
}
