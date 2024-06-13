/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:20:33 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/13 04:47:08 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "exec_pipelist_bonus.h"

static void	exec_subshell(t_cmd *pipelist, t_env **env, t_cmd *data)
{
	int		exit_code;

	exit_code = exec_pipelist(pipelist, env, data);
	minishell_free(data, NULL, NULL, *env);
	exit(exit_code);
}

// not exit if pid = -1 because need to wait the other fork
int	process(t_cmd *cmd, int *fd_in, t_env **env, t_cmd *data)
{
	int		pid;
	int		pipe_out[2];

	if (cmd->next && pipe_ms(pipe_out))
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		handle_pipe_child(fd_in, pipe_out, cmd);
		if (exec_redir(cmd->redir, *env) != SUCCESS)
			exit_on_failure(data, NULL, NULL, *env);
		if (cmd->flag == SUB)
			exec_subshell(cmd->pipelist, env, data);
		exec_cmd_pipe(cmd, env, data);
	}
	if (pid == -1)
	{
		perror("minishell: process_pipes: fork");
		if (cmd->next)
			close(pipe_out[READ]);
	}
	handle_pipe_parent(fd_in, pipe_out, cmd);
	return (pid);
}
