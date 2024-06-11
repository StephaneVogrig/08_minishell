/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:57:51 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 04:01:21 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_bonus.h"

t_bool	wc_list_add_str(char *str, t_wildcard *wc)
{
	if (ft_lstadd_back_new(&wc->list, str) == FAILURE)
	{
		perror("minishell: wc_list_add_str: ft_lstadd_back_new");
		return (FAILURE);
	}
	return (SUCCESS);
}

void	wc_free(t_wildcard *wc)
{
	t_list	*node;
	t_list	*temp;

	node =  wc->list;
	while (node)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
	wc->list = NULL;
}

int	ft_strcmp_rev(const char *big, const char *little)
{
	int	i;
	int j;

	i = ft_strlen(big) - ft_strlen(little);
	j = 0;
	if ( i < 0)
		return (-1);
	while (little[j])
	{
		if (big[i] == '\0' || big[i] != little[j])
			return ((unsigned char)big[i] - (unsigned char)little[j]);
		i++;
		j++;
	}
	return (0);
}

char	*mini_strstr(const char *big, const char *little)
{
	int	i;

	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (*big)
	{
		if (*big == *little)
		{
			i = 0;
			while (big[i] == little[i] && big[i])
				i++;
			if (little[i] == '\0')
				return ((char *)(big + i));
		}
		big++;
	}
	return (NULL);
}
