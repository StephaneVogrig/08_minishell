/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:44:43 by stephane          #+#    #+#             */
/*   Updated: 2024/06/02 18:15:48 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "heredoc.h"

static char	*heredoc_expanse(int fd, char *str, t_env *env)
{
	char	*end;
	char	*expand;
	int		i;

	if (*str == '?')
	{
		expand = env_get(env, "?");
		ft_putstr_fd(expand, fd);
		return (str + 1);
	}
	end = end_name(str);
	i = end - str;
	if (i == 0)
	{
		write(fd, "$", 1);
		return (str);
	}
	str = env_get_n(env, str, i);
	ft_putstr_fd(str, fd);
	return (end);
}

static void	heredoc_expand_write(int fd, char *input, t_env *env)
{
	int	i;

	i = 0;
	while (1)
	{
		if (!input[i])
		{
			write(fd, input, i);
			break ;
		}
		if (input[i] == '$')
		{
			write(fd, input, i);
			input = heredoc_expanse(fd, &input[i + 1], env);
			i = 0;
			continue ;
		}
		i++;
	}
}

static void	heredoc_expand_loop(int fd_src, int fd_dest, t_env *env)
{
	char	*str;

	str = get_next_line(fd_src);
	while (str)
	{
		heredoc_expand_write(fd_dest, str, env);
		free(str);
		str = get_next_line(fd_src);
	}
}

t_bool	heredoc_expand(t_redir *redir, t_env *env)
{
	int		fd_src;
	int		fd_dest;

	fd_src = open(redir->str, O_RDONLY);
	if (fd_src == -1)
	{
		perror("minishell: heredoc_expand");
		return (FAILURE);
	}
	unlink(redir->str);
	fd_dest = open(redir->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_src == -1)
	{
		close(fd_src);
		perror("minishell: heredoc_expand");
		return (FAILURE);
	}
	heredoc_expand_loop(fd_src, fd_dest, env);
	close(fd_src);
	close(fd_dest);
	return (SUCCESS);
}
