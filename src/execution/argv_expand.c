/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:06:16 by stephane          #+#    #+#             */
/*   Updated: 2024/06/02 20:13:29 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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