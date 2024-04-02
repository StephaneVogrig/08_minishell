/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:13:04 by smortemo          #+#    #+#             */
/*   Updated: 2024/02/06 12:13:44 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	len_d;
	unsigned int	len_s;

	if ((!dst && size == 0) || (!src && size == 0))
		return (0);
	len_s = ft_strlen(src);
	len_d = ft_strlen(dst);
	j = len_d;
	i = 0;
	if (size == 0)
		return (len_s);
	if (size >= len_d && size - len_d >= 1)
	{
		while (i < (size - len_d - 1) & src[i] != '\0' )
			dst[j++] = src[i++];
		dst[j] = '\0';
	}
	if (size < len_d)
		return (len_s + size);
	else
		return (len_s + len_d);
}
