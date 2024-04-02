/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:22:37 by smortemo          #+#    #+#             */
/*   Updated: 2024/03/19 15:31:19 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char		**ft_split(char const *s, char c);
static int	nbr_of_words(const char *str, char c);
static char	**sub_malloc(const char *s, char c, char **tab, int count);
static int	str_end_cut(const char *str, char c);
static char	**free_tab(char **tab, int k);

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		count;
	size_t	i;

	i = 0;
	count = 0;
	tab = NULL;
	while (s[i] && s[i] == c)
		i++;
	if (!s)
		return (NULL);
	if (i == ft_strlen(s))
	{
		tab = malloc(sizeof(char *) * (2));
		tab[0] = ft_strdup(s);
		tab[1] = NULL;
		return (tab);
	}
	count = nbr_of_words(s, c);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	sub_malloc(s, c, tab, count);
	return (*&tab);
}

static char	**sub_malloc(const char *s, char c, char **tab, int count)
{
	int	i;
	int	k;
	int	len;
	int	j;

	j = 0;
	len = 0;
	i = 0;
	k = 0;
	while (k < count)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		len = str_end_cut(&s[i], c);
		tab[k] = malloc(sizeof(char) * (len + 1));
		if (!tab[k])
			return (free_tab(tab, k));
		while (j < len)
			tab[k][j++] = s[i++];
		tab[k][j] = '\0';
		j = 0;
		k++;
	}
	tab[k] = NULL;
	return (*&tab);
}

static char	**free_tab(char **tab, int k)
{
	while (k >= 0)
	{
		free(tab[k]);
		k--;
	}
	free(tab);
	return (NULL);
}

static int	str_end_cut(const char *str, char c)
{
	unsigned int	len;

	len = 0;
	while (str[len] != c && str[len] != '\0')
		len++;
	return (len);
}

static int	nbr_of_words(const char *str, char c)
{
	unsigned int	i;
	unsigned int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
		else if (str[i] == c)
			i++;
	}
	return (count);
}
