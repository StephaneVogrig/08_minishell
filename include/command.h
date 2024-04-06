/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:33:09 by stephane          #+#    #+#             */
/*   Updated: 2024/04/05 12:24:02 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef COMMAND_H
# define COMMAND_H

#include "libft.h"

typedef struct s_cmd{
	t_list			*heredoc;
	char			*in;
	char			*out;
	t_bool			append_out;
	t_list			*argv;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*cmd_new(void);
void	cmd_free(t_cmd *cmd);
void	pipeline_free(t_cmd **pipeline);

#endif