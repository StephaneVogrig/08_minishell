/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:13:37 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/05 21:35:50 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*str_join;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str_join = ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	if (!str_join)
		return (NULL);
	ft_strlcpy(str_join, s1, len_s1 + 1);
	ft_strlcpy(str_join + len_s1, s2, len_s2 + 1);
	return (str_join);
}

char	*ft_strjoin_free_s1(char const *s1, char const *s2)
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
	free((char *)s1);
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