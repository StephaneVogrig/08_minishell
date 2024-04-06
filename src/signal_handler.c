/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:07:09 by stephane          #+#    #+#             */
/*   Updated: 2024/04/04 18:22:26 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "signal_handler.h"

void	handler_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
		// prompt_print();
	}
}
