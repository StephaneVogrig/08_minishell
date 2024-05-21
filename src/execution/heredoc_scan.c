/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_scan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:05:04 by stephane          #+#    #+#             */
/*   Updated: 2024/05/21 17:07:01 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

char	*heredoc_expanse(int fd, char *str,t_env *env)
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

void	heredoc_save_expanse(int fd, char *input, t_env *env)
{
	int	i;

	i = 0;
	while (1)
	{
		if (!input[i])
		{
			write(fd, input, i);
			write(fd, "\n", 1);
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

t_bool	is_scan_end(char *input, char *limiter)
{
	if (!input)
	{
		fd_printf(STDERR_FD, "minishell: warning: here-document delimited by end-of-file\n");
		return (TRUE);
	}
	if (ft_strcmp(input, limiter) == 0)
	{
		free(input);
		return (TRUE);
	}
	return (FALSE);
}

int	heredoc_scan(int fd, t_redir *redir, t_env *env)
{
	char	*input;

	while (1)
	{
		input = readline(">");
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			free(input);
			return (128 + SIGINT);
		}
		if (is_scan_end(input, redir->str))
			break ;
		if (redir->type & EXPANSE)
			heredoc_save_expanse(fd, input, env);
		else
			fd_printf(fd, "%s\n", input);
		free(input);		
	}
	return (SUCCESS);
}
