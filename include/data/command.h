/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:33:09 by stephane          #+#    #+#             */
/*   Updated: 2024/06/18 16:05:20 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "libft.h"
# include "redirection.h"

typedef struct s_cmd	t_cmd;
typedef t_cmd			t_cmd_m;

struct s_cmd{
	t_redir	*redir;
	union {
		t_list	*argv;
		t_cmd	*pipeline;
		t_cmd	*pipelist;
	};
	t_cmd	*next;
	t_cmd	*previous;
	pid_t	pid;
	int		flag;
};

# define PIPE 1
# define AND 2
# define OR	4
# define CMDLIST 8
# define SUB 16
# define IN_SUB 32

t_cmd_m	*cmd_new(void);
void	cmd_free(t_cmd_m *cmd);
int		cmd_nbr(t_cmd *pipeline);

#endif
