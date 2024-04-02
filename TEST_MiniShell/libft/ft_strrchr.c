/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:52:09 by smortemo          #+#    #+#             */
/*   Updated: 2024/03/19 15:31:11 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	int			len;
	const char	*r;

	if (!s || s[0] == '\0')
		return (NULL);
	len = ft_strlen(s);
	r = s;
	i = len;
	if (c == '\0')
	{
		r = &s[i];
		return ((char *)r);
	}
	while (i >= 0)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
		{
			r = &s[i];
			return ((char *)r);
		}
		i--;
	}
	return (0);
}
