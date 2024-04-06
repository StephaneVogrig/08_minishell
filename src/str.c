/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:52:14 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/05 13:28:03 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "str.h"

t_bool	is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}

void	pipex_strncpy(char *dest, char *src, int n)
{
	while (n-- && *src)
		*dest++ = *src++;
	*dest = '\0';
}

t_bool	add_to_strlist(t_list **strlist, char *str)
{
	t_list	*new_node;

	new_node = ft_lstnew(str);
	if (!new_node)
	{
		perror("pipex: add_to_strlist");
		ft_lstclear(strlist, &free);
		return (FAILURE);
	}
	ft_lstadd_back(strlist, new_node);
	return (SUCCESS);
}

char	**argv_empty(void)
{
	char	**argv;
	char	*empty_str;

	argv = NULL;
	empty_str = ft_calloc(1, 1);
	if (!empty_str)
		exit_perror("pipex: argv_empty: calloc");
	argv = malloc(sizeof(char *) * 2);
	if (!argv)
	{
		free(empty_str);
		exit_perror("pipex: argv_empty: malloc");
	}
	argv[0] = empty_str;
	argv[1] = NULL;
	return (argv);
}
