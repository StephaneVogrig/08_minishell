/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 05:44:26 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/31 16:09:21 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv.h"

t_bool	strlist_add_str(t_list **strlist, char *str)
{
	t_list	*new_node;

	new_node = ft_lstnew(str);
	if (!new_node)
	{
		perror("minishell: strlist_add_str");
		ft_lstclear(strlist, &free);
		return (FAILURE);
	}
	ft_lstadd_back(strlist, new_node);
	return (SUCCESS);
}

t_bool	strlist_add_buffer(t_list **argv, t_buff *buffer)
{
	t_char_m	*token;

	token = buff_to_str(buffer);
	buff_clear(buffer);
	if (!token)
		return (FAILURE);
	return (strlist_add_str(argv, token));
}

char	**strlist_to_strtab(t_list *strlist)
{
	char	**strtab;
	char	**temptab;
	t_list	*templist;

	strtab = malloc(sizeof(strtab) * (ft_lstsize(strlist) + 1));
	if (!strtab)
	{
		perror("minishell: strlist_to_strtab");
		return (NULL);
	}
	temptab = strtab;
	while (strlist)
	{
		*temptab++ = strlist->content;
		templist = strlist->next;
		free(strlist);
		strlist = templist;
	}
	*temptab = NULL;
	return (strtab);
}

char	**argvlist_to_argvtab(t_list **argvlist)
{
	char	**argvtab;

	argvtab = strlist_to_strtab(*argvlist);
	if (!argvtab)
		return (NULL);
	*argvlist = NULL;
	return (argvtab);
}
