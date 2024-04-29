/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:52:14 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/29 05:10:16 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

t_bool	is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}

t_bool	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (TRUE);
	return (FALSE);
}

char	*skip_blank(char *str)
{
	if (!str)
		return (NULL);
	while (is_blank(*str))
		str++;		
	return (str);	
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
		perror("minishell: add_to_strlist");
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
	{
		perror("minishell: argv_empty: calloc");
		exit(EXIT_FAILURE);
	}
	argv = malloc(sizeof(char *) * 2);
	if (!argv)
	{
		free(empty_str);
		perror("minishell: argv_empty: malloc");
		exit(EXIT_FAILURE);
	}
	argv[0] = empty_str;
	argv[1] = NULL;
	return (argv);
}

char	**strlist_to_strtab(t_list *strlist)
{
	int		nbr_elem;
	char	**strtab;
	char	**argv;
	t_list	*temp;

	if (!strlist)
		return (NULL);
	nbr_elem = ft_lstsize(strlist);
	argv = malloc(sizeof(argv) * (nbr_elem + 1));
	if (!argv)
	{
		perror("minishell: charlist_to_chartab");
		return (NULL);
	}
	strtab = argv;
	while (nbr_elem--)
	{
		*strtab++ = strlist->content;
		temp = strlist->next;
		free(strlist);
		strlist = temp;
	}
	*strtab = NULL;
	return (argv);
}
