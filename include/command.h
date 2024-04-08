/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:33:09 by stephane          #+#    #+#             */
/*   Updated: 2024/04/08 03:19:30 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

#include "libft.h"
#include "redirection.h"

typedef struct s_cmd{
	t_list			*heredoc;
	t_redir			*redir;
	t_list			*argv;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*cmd_new(void);
void	cmd_free(t_cmd *cmd);
int		cmd_nbr(t_cmd *pipeline);

#endif