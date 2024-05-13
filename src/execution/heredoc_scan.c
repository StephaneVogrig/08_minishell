/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_scan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:05:04 by stephane          #+#    #+#             */
/*   Updated: 2024/05/13 15:10:51 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "heredoc.h"

char	*heredoc_expanse(int fd, char *str,t_env *env, int *exit_status)
{
	char	*end;
	char	*expand;
	int		i;

	if (*str == '?')
	{
		expand = ft_itoa(*exit_status);
		if (!expand)
			return (NULL);
		ft_putstr_fd(expand, fd);
		free (expand);
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

void	heredoc_save_expanse(int fd, char *input, t_env *env, int *exit_status)
{
	int	i;

	i = 0;;
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
			input = heredoc_expanse(fd, &input[i + 1], env, exit_status);
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

int	heredoc_scan(int fd, t_redir *redir, t_env *env, int *exit_status)
{
	char	*input;
	extern int	g_global;

	while (1)
	{
		input = readline(">");
		if (g_global == SIGINT)
		{
			free(input);
			return (130);
		}
		if (is_scan_end(input, redir->str))
			break ;
		if (redir->type & EXPANSE)
			heredoc_save_expanse(fd, input, env, exit_status);
		else
			fd_printf(fd, "%s\n", input);
		free(input);		
	}
	return (SUCCESS);
}
