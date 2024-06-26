/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:13:37 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/12 22:43:17 by svogrig          ###   ########.fr       */
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
	char			*str;

	str = ft_strjoin(s1, s2);
	if (s1)
		free ((char *) s1);
	return (str);
}

char	*ft_strjoin_free_s2(char const *s1, char const *s2)
{
	char			*str;

	str = ft_strjoin(s1, s2);
	if (s2)
		free((char *)s2);
	return (str);
}
