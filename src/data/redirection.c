/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:36:10 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/06 18:58:05 by svogrig          ###   ########.fr       */
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

t_bool	redirection_add(t_redir **redirs, t_char_m *str, int type)
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
