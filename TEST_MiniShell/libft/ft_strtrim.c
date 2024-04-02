/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:35:30 by smortemo          #+#    #+#             */
/*   Updated: 2023/11/14 14:10:12 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*tab;
	int		l;
	int		len_total;
	int		k;

	if (!s1)
		return (NULL);
	k = 0;
	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]) != 0)
		i++;
	l = ft_strlen(s1) - 1;
	while (l > i && ft_strchr(set, s1[l]) != 0)
		l--;
	len_total = l - i + 1;
	tab = (char *) malloc (sizeof (char) * (len_total + 1));
	if (!tab)
		return (0);
	while (k < len_total)
		tab[k++] = s1[i++];
	tab[k] = '\0';
	return (tab);
}
