/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:37:10 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/18 20:02:30 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_redir.h"

static int	redir_open(char *str, int type)
{
	int	fd;

	if (type & IN)
		fd = open(str, O_RDONLY);
	else if (type & APPEND)
		fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

static t_bool	redir_expand_and_dequote(t_redir *redir, t_env *env)
{
	t_list	*strlist;

	errno = 0;
	strlist = NULL;
	if (redir->type & (HEREDOC | EXPANSE))
		return (heredoc_expand(redir, env));
	if (expand_and_dequote(redir->str, &strlist, env) == FAILURE)
		return (FAILURE);
	if (!strlist || strlist->next)
	{
		fd_printf(STDERR_FD, "minishell: %s: ambiguous redirect\n", redir->str);
		ft_lstclear(&strlist, free);
		return (FAILURE);
	}
	free(redir->str);
	redir->str = strlist->content;
	free(strlist);
	return (SUCCESS);
}

t_bool	exec_redir(t_redir *redirs, t_env *env)
{
	int		fd;

	while (redirs)
	{
		if (redir_expand_and_dequote(redirs, env) == FAILURE)
			return (FAILURE);
		fd = redir_open(redirs->str, redirs->type);
		if (fd == -1)
		{
			fd_printf(STDERR_FILENO, "minishell: %s: %s\n", redirs->str,
				strerror(errno));
			return (-1);
		}
		if (redirs->type & IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redirs = redirs->next;
	}
	return (SUCCESS);
}
