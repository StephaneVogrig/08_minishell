/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:15:39 by smortemo          #+#    #+#             */
/*   Updated: 2023/11/15 14:40:59 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*tab;
	size_t		k;

	if (!s)
		return (0);
	if (len == 0)
		return (ft_calloc(1, 1));
	if (start > ft_strlen(s))
		return (ft_calloc(1, 1));
	else if (len >= ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	tab = NULL;
	tab = (char *) malloc (sizeof (char) * len + 1);
	if (!tab)
		return (NULL);
	i = start;
	k = 0;
	while (k <= len)
		tab[k++] = s[i++];
	tab[len] = '\0';
	return (tab);
}
