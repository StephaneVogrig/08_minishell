/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_scan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:05:04 by stephane          #+#    #+#             */
/*   Updated: 2024/06/03 16:15:24 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

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

static int	event(void)
{
	return (0);
}

int	heredoc_scan(int fd, t_redir *redir)
{
	char	*input;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			rl_event_hook = event;
			input = readline(">");
			rl_event_hook = NULL;
		}
		else
			input = get_next_line(fd);
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
