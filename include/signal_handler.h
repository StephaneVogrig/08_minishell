/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:08:46 by stephane          #+#    #+#             */
/*   Updated: 2024/04/04 17:25:36 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include <unistd.h>
# include <signal.h>
# include "prompt.h"
# include <readline/readline.h>

void	handler_ctrl_c(int signal);

#endif