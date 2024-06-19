/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortlist_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:11:00 by stephane          #+#    #+#             */
/*   Updated: 2024/06/19 16:54:50 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sortlist_bonus.h"

int	mini_strcmp(char *s1, char *s2)
{
	char	c1;
	char	c2;
	int		order_noalphanum;
	int		order_alphanum;

	order_noalphanum = 0;
	order_alphanum = 0;
	while (*s1)
	{
		c1 = ft_tolower(*s1);
		c2 = ft_tolower(*s2);
		if (c1 != c2)
			return (c1 - c2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	insert(t_list *elem, t_list **strlist)
{
	t_list	*previous;
	t_list	*current;

	previous = NULL;
	current = *strlist;
	while (current && mini_strcmp(current->content, elem->content) <= 0)
	{
		previous = current;
		current = current->next;
	}
	elem->next = current;
	if (previous)
		previous->next = elem;
	else
		*strlist = elem;
}

t_list	*pop(t_list **strlist)
{
	t_list	*temp;

	if (*strlist == NULL)
		return (NULL);
	temp = *strlist;
	*strlist = temp->next;
	return (temp);
}

void	sort_strlist(t_list **strlist)
{
	t_list	*temp;
	t_list	*sorted;

	sorted = NULL;
	while (*strlist)
	{
		temp = pop(strlist);
		insert(temp, &sorted);
	}
	*strlist = sorted;
}
