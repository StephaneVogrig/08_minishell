/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:08:11 by smortemo          #+#    #+#             */
/*   Updated: 2024/02/21 20:19:17 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free_s1(char const *s1, char const *s2)
{
	unsigned int	i;
	char			*tab;
	int				k;

	tab = NULL;
	if (s1 == 0 || s2 == 0)
		return (malloc(0));
	tab = (char *) malloc (sizeof (char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!tab)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
		tab[k++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		tab[k++] = s2[i++];
	tab[k] = '\0';
	free ((char *) s1);
	return (tab);
}

char	*ft_strjoin_free_s2(char const *s1, char const *s2)
{
	unsigned int	i;
	char			*tab;
	int				k;

	tab = NULL;
	if (s1 == 0 || s2 == 0)
		return (malloc(0));
	tab = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!tab)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
		tab[k++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		tab[k++] = s2[i++];
	tab[k] = '\0';
	free((char *)s2);
	return (tab);
}
