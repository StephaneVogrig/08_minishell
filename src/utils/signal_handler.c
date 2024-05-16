/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:07:09 by stephane          #+#    #+#             */
/*   Updated: 2024/05/16 21:20:06 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"

volatile sig_atomic_t	g_signal;

void	handler_ctrl_c(int sigint)
{
	signal(sigint, SIG_IGN);
	if (g_signal != SIGINT)
		write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("",0);
	rl_redisplay();
	signal(sigint, handler_ctrl_c);
}

void	handler_ctrl_c_heredoc(int sigint)
{
	signal(sigint, SIG_IGN);
	g_signal = SIGINT;
	int	fds[2];
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("",0);
	pipe(fds);
	dup2(fds[0], 0);
	close (fds[0]);
	close (fds[1]);
}