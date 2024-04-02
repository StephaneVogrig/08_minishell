/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:24:06 by smortemo          #+#    #+#             */
/*   Updated: 2024/03/19 15:31:34 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	char			*tab;
	int				k;

	if (!s2)
		return (NULL);
	tab = NULL;
	if (s1 == 0)
		return (malloc(0));
	tab = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!tab)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		tab[k++] = s1[i++];
	}
	i = 0;
	while (s2[i] != '\0')
	{
		tab[k++] = s2[i++];
	}
	tab[k] = '\0';
	return (tab);
}
