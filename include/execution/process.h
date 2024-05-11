/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 22:21:43 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/07 04:42:11 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include <fcntl.h>
# include "builtin.h"
# include "command.h"
# include "exec_cmd.h"
# include "pipe.h"

int		process_first(t_cmd *cmd, int *fd_out, t_env *env, int *pids);
int		process_pipes(t_cmd *cmd, int *fd_in, t_env *env, int *pids);
int		process_last(t_cmd *cmd, int fd_in, t_env *env, int *pids);

#endif