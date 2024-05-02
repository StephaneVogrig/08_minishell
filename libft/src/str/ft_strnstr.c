/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:04:07 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/02 23:25:18 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;

	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (len && *big)
	{
		if (*big == *little)
		{
			i = 0;
			while (big[i] == little[i] && (len - i) && big[i])
				i++;
			if (little[i] == '\0')
				return ((char *)big);
		}
		big++;
		len--;
	}
	return (NULL);
}

int	ft_strstr(const char *big, const char *little)
{
	int	i;

	if (ft_strlen(little) == 0)
		return (0);
	while (*big)
	{
		if (*big == *little)
		{
			i = 0;
			while (big[i] == little[i] && big[i])
				i++;
			if (little[i] == '\0')
				return (i);
		}
		big++;
	}
	return (0);
}
