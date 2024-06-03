/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:33:09 by stephane          #+#    #+#             */
/*   Updated: 2024/06/03 19:39:58 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "libft.h"
# include "redirection.h"

typedef struct s_cmd{
	t_redir			*redir;
	t_list			*argv;
	struct s_cmd	*next;
	struct s_cmd	*previous;
	pid_t			pid;
	int				flag;
}	t_cmd;

typedef t_cmd	t_cmd_m;

# define PIPE 1
# define AND 2
# define OR	4
# define SUB 8

t_cmd_m	*cmd_new(void);
void	cmd_free(t_cmd_m *cmd);
int		cmd_nbr(t_cmd *pipeline);

#endif