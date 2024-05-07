/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:07:09 by stephane          #+#    #+#             */
/*   Updated: 2024/05/07 18:50:51 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"

void	handler_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
	}
}

void	handler_ctrl_c_heredoc(int signal)
{
	extern int	g_global;

	if (signal == SIGINT)
	{
		g_global = SIGINT;
		write(1, "\n", 1);
		// rl_on_new_line();
		// rl_replace_line("",0);
		// rl_redisplay();
	}
}