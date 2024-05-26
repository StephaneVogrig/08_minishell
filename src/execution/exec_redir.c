/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:37:10 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/27 01:07:05 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_redir.h"

int	redir_open(char *str, int type)
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

t_bool	expand_and_dequote(char *str, t_list **strlist, t_env *env)
{
	t_buff	buffer;

	if (is_token_empty(str, env))
		return (SUCCESS);
	buff_init(&buffer);
	while (str && *str)
	{
		if (*str == '\'')
			str = parse_spl_quoted(&buffer, str);
		else if (*str == '\"')
			str = parse_dbl_quoted(&buffer, str, env);
		else if (*str == '$')
			str = expanse_unquoted(&buffer, ++str, strlist, env);
		else if (buff_add_char(&buffer, *str++) == FAILURE)
			str = NULL;
	}
	if (str && strlist_add_buffer(strlist, &buffer) == FAILURE)
		str = NULL;
	buff_clear(&buffer);
	if (str)
		return (SUCCESS);
	ft_lstclear(strlist, free);
	return (FAILURE);
}

t_bool	redir_expand_and_dequote(t_redir *redir, t_env *env)
{
	t_list	*strlist;

	errno = 0;
	strlist = NULL;
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
			redirlist_unlink_heredoc(redirs);
			return (FAILURE);
		}
		if (redirs->type & IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		if (redirs->type & HEREDOC)
			unlink(redirs->str);
		redirs = redirs->next;
	}
	return (SUCCESS);
}
