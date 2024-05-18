/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:08:46 by stephane          #+#    #+#             */
/*   Updated: 2024/05/18 01:06:32 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>

extern volatile sig_atomic_t	g_signal;

void	handler_ctrl_c(int sigint);
void	handler_ctrl_c_interactive(int signal);
void	handler_ctrl_c_heredoc(int signal);
void	handler_ctrl_c_file(int signal);

#endif