/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 04:15:23 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/13 04:32:03 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

// not exit if pid = -1 because need to wait the other fork
int	process(t_cmd *cmd, int *fd_in, t_env **env, t_cmd *data)
{
	int		pid;
	int		pipe_out[2];

	if (cmd->next)
		if (pipe_ms(pipe_out))
			return (-1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		handle_pipe_child(fd_in, pipe_out, cmd);
		if (exec_redir(cmd->redir, *env) != SUCCESS)
			exit_on_failure(cmd, NULL, NULL, *env);
		exec_cmd_pipe(cmd, env, data);
	}
	if (pid == -1)
	{
		perror("minishell: process: fork");
		if (cmd->next)
			close(pipe_out[READ]);
	}
	handle_pipe_parent(fd_in, pipe_out, cmd);
	return (pid);
}
