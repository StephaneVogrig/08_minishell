/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 04:15:23 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/04 22:39:47 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

void	process_exec_cmd(t_cmd *cmd, t_env *env)
{
	int	exit_status;

	exit_status = 0;
	if (builtin_is_executed(cmd, env, &exit_status))
	{
		cmd_free(cmd);
		env_free(env);
		exit(exit_status);
	}
	else
		exec_cmd(cmd, env);
}

int	process_first(t_cmd *cmd, int *fd_out, t_env *env, int *pids)
{
	int	pid;
	int	pipe_out[2];

	if (pipe_ms(pipe_out))
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		free(pids);
		close(pipe_out[READ]);
		dup2(pipe_out[WRITE], STDOUT_FD);
		close(pipe_out[WRITE]);
		process_exec_cmd(cmd, env);
	}
	if (pid == -1)
	{
		perror("minishell: process_first: fork");
		close(pipe_out[READ]);
	}
	close(pipe_out[WRITE]);
	*fd_out = pipe_out[READ];
	return (pid);
}

int	process_pipes(t_cmd *cmd, int *fd_in, t_env *env, int *pids)
{
	int	pid;
	int	pipe_out[2];

	if (pipe_ms(pipe_out))
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		free(pids);
		dup2(*fd_in, STDIN_FD);
		close(*fd_in);
		close(pipe_out[READ]);
		dup2(pipe_out[WRITE], STDOUT_FD);
		close(pipe_out[WRITE]);
		process_exec_cmd(cmd, env);
	}
	if (pid == -1)
	{
		perror("minishell: process_pipes: fork");
		close(pipe_out[READ]);
	}
	close(*fd_in);
	close(pipe_out[WRITE]);
	*fd_in = pipe_out[READ];
	return (pid);
}

int	process_last(t_cmd *cmd, int fd_in, t_env *env, int *pids)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		free(pids);
		dup2(fd_in, STDIN_FD);
		close(fd_in);
		process_exec_cmd(cmd, env);
	}
	if (pid == -1)
		perror("minishell: process_last: fork");
	close(fd_in);
	return (pid);
}
