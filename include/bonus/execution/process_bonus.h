/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:21:05 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 14:54:51 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_BONUS_H
# define PROCESS_BONUS_H

# include <fcntl.h>
# include "builtin.h"
# include "command.h"
# include "exec_cmd_bonus.h"
# include "pipe.h"
# include "exec_redir.h"
# include "argv_expand.h"

# include "pipelist_bonus.h"
# include "exec_pipelist_bonus.h"
# include "exit_bonus.h"

int	process(t_cmd *cmd, int *fd_in, t_env **env, t_cmd *tofree);

#endif
