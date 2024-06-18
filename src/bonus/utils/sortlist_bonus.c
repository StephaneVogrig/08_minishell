/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortlist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:11:00 by stephane          #+#    #+#             */
/*   Updated: 2024/06/18 17:41:37 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sortlist_bonus.h"

t_list	*pop(t_list **strlist)
{
	t_list	*temp;

	if (*strlist == NULL)
		return (NULL);
	temp = *strlist;
	*strlist = temp->next;
	return (temp);
}

void	insert(t_list *elem, t_list **strlist)
{
	t_list	*previous;
	t_list	*current;

	previous = NULL;
	current = *strlist;
	while (current && ft_strcmp(current->content, elem->content) <= 0)
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
