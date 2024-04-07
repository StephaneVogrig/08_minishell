/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:33:09 by stephane          #+#    #+#             */
/*   Updated: 2024/04/06 21:48:39 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
int		cmd_nbr(t_cmd *pipeline);

#endif