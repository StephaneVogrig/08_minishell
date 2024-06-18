/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:36:10 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/18 20:01:21 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static void	redir_add_back(t_redir *redirs, t_redir *node)
{
	while (redirs->next)
		redirs = redirs->next;
	redirs->next = node;
}

t_bool	redir_add_str(t_redir **redirs, t_char_m *str, int type)
{
	t_redir	*new_redir;

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
	redir_add_back(*redirs, new_redir);
	return (SUCCESS);
}

void	redirection_free(t_redir **redirs)
{
	t_redir	*temp;

	while (*redirs)
	{
		temp = (*redirs)->next;
		if ((*redirs)->str)
		{
			if ((*redirs)->type & UNLINK)
				unlink((*redirs)->str);
			free((*redirs)->str);
		}
		free(*redirs);
		*redirs = temp;
	}
}
