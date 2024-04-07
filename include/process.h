/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 22:21:43 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/07 02:39:23 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include <fcntl.h>
# include "command.h"
# include "pipex_const.h"
# include "exec_cmd.h"
# include "pipex_bonus.h"

int		process_infile(t_cmd *cmd, int *pipe_out, char **envp, int *pids);
int		process_pipes(t_cmd *cmd, int *fd_in, char **envp, int *pids);
int		process_outfile(t_cmd *cmd, int fd_in, char **envp, int *pids);

#endif