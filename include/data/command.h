/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:33:09 by stephane          #+#    #+#             */
/*   Updated: 2024/05/07 00:01:42 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

#include "libft.h"
#include "redirection.h"

typedef struct s_cmd{
	t_redir			*redir;
	t_list			*argv;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}	t_cmd;

typedef t_cmd t_cmd_m;

t_cmd_m	*cmd_new(void);
void	cmd_free(t_cmd_m *cmd);
int		cmd_nbr(t_cmd *pipeline);

#endif