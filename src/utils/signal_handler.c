/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:07:09 by stephane          #+#    #+#             */
/*   Updated: 2024/06/05 17:45:56 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"

volatile sig_atomic_t	g_signal;

void	handler_ctrl_c(int sigint __attribute__((unused)))
{
	write(2, "\n", 1);
}

void	handler_ctrl_c_interactive(int sigint)
{
	signal(sigint, SIG_IGN);
	g_signal = SIGINT;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	signal(sigint, handler_ctrl_c_interactive);
}

void	handler_ctrl_c_heredoc(int sigint)
{
	signal(sigint, SIG_IGN);
	g_signal = SIGINT;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
}

void	handler_ctrl_c_file(int sigint __attribute__((unused)))
{
	g_signal = SIGINT;
}
