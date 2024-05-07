/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:36:10 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/07 06:12:42 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

int	is_directory(char *path)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
		close(fd);
	return (fd >= 0);
}

t_bool	redir_add_str(t_redir **redirs, t_char_m *str, int type)
{
	t_redir	*new_redir;
	t_redir	*temp;

	new_redir = malloc(sizeof(*new_redir));
	if (!new_redir)
	{
		perror("minishell: add_to_redirection");
		return (FAILURE);
	}
	new_redir->str = str;
	new_redir->type = type;
	new_redir->next = NULL;
	if (!*redirs)
	{
		*redirs = new_redir;
		return (SUCCESS);
	}
	temp = *redirs;
	while (temp->next)
		temp = temp->next;
	temp->next =  new_redir;
	return (SUCCESS);
}

t_bool	redir_add_strlist(t_list *strlist, int type, t_redir **redir, char *str)
{
	if (!strlist)
		return (FAILURE);
	if (strlist->next)
	{
		fd_printf(STDERR_FD, "minishell: %s: ambiguous redirect\n", str);
		ft_lstclear(&strlist, free);
		return (FAILURE);
	}
	if (!redir_add_str(redir, strlist->content, type))
	{
		ft_lstclear(&strlist, free);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	redirection_free(t_redir **redirs)
{
	t_redir	*temp;

	while (*redirs)
	{	
		temp = (*redirs)->next;
		if ((*redirs)->str)
			free((*redirs)->str);
		free(*redirs);
		*redirs = temp;
	}
}
