/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_scan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:05:04 by stephane          #+#    #+#             */
/*   Updated: 2024/06/11 23:32:46 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

int	mini_rand(int num, int i)
{
	int	mod;
	int	mult;

	mod = INT_MAX;
	mult = 48271;
	num = (mult * num + i) % mod;
	if (num < 0)
		num = -num;
	return (num);
}

char	*get_path_temp(void)
{
	int		num;
	int		i;
	char	*hdt;

	num = 12345;
	i = 0;
	while (1)
	{
		num = mini_rand(num, i);
		hdt = ft_itoa(num);
		if (!hdt)
			return (NULL);
		hdt = ft_strjoin_free_s2("/tmp/minishell_temp_", hdt);
		if (!hdt)
			return (NULL);
		if (access(hdt, F_OK) == -1)
			return (hdt);
		free(hdt);
		i++;
	}
	return (NULL);
}

static t_bool	is_scan_end(char *input, char *limiter)
{
	if (!input)
	{
		fd_printf(STDERR_FD,
			"minishell: warning: here-document delimited by end-of-file\n");
		return (TRUE);
	}
	if (ft_strcmp(input, limiter) == 0)
	{
		free(input);
		return (TRUE);
	}
	return (FALSE);
}

int	heredoc_scan(int fd, t_redir *redir)
{
	char	*input;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			rl_event_hook = heredoc_readline_event;
			input = readline(">");
			rl_event_hook = NULL;
		}
		else
			input = get_next_line(STDIN_FILENO);
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			free(input);
			return (128 + SIGINT);
		}
		if (is_scan_end(input, redir->str))
			break ;
		fd_printf(fd, "%s\n", input);
		free(input);
	}
	return (SUCCESS);
}

int	heredoc_fill(t_redir *redir)
{
	char	*path;
	int		fd;
	int		exit_code;

	path = get_path_temp();
	if (path == NULL)
		return (FAILURE);
	fd = open(path, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("minishell: heredoc_fill: open");
		free(path);
		return (FAILURE);
	}
	exit_code = heredoc_scan(fd, redir);
	free(redir->str);
	redir->str = path;
	close(fd);
	return (exit_code);
}
