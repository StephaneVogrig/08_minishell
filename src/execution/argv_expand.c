/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:06:16 by stephane          #+#    #+#             */
/*   Updated: 2024/06/03 16:27:39 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv_expand.h"

t_bool	argv_expand(t_list **argvlist, t_env *env)
{
	t_list	*temp;
	t_list	*expanded;

	temp = *argvlist;
	expanded = NULL;
	while (temp)
	{
		if (expand_and_dequote(temp->content, &expanded, env) == FAILURE)
			return (FAILURE);
		temp = temp->next;
	}
	ft_lstclear(argvlist, free);
	*argvlist = expanded;
	return (SUCCESS);
}
