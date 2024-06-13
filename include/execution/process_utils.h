/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 01:20:20 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/13 03:36:08 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_UTILS_H
# define PROCESS_UTILS_H

# include <unistd.h>
# include "pipe.h"
# include "command.h"
# include "builtin.h"
# include "exec_cmd.h"
# include "argv_expand.h"

void	exec_cmd_pipe(t_cmd *cmd, t_env **env, t_cmd *data);
void	handle_pipe_child(int *fd_in, int pipe_out[2], t_cmd *cmd);
void	handle_pipe_parent(int *fd_in, int pipe_out[2], t_cmd *cmd);

#endif
