/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:28:23 by smortemo          #+#    #+#             */
/*   Updated: 2023/11/17 11:59:59 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*tab;

	tab = 0;
	i = 0;
	if (nmemb == 0 || size == 0)
		return (malloc (0));
	if ((int)nmemb < 0 || (int)size < 0)
		return (0);
	else
	{
		tab = malloc (nmemb * size);
		if (!tab)
			return (0);
		while (i < (nmemb * size))
		{
			tab[i] = 0 ;
			i++;
		}
		return ((void *)tab);
	}
}
