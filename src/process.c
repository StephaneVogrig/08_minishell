/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 04:15:23 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/08 04:15:27 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

int	process_first(t_cmd *cmd, int *fd_out, char **envp, int *pids)
{
	int		pid;
	int		pipe_out[2];

	if (pipe_ms(pipe_out))
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		free(pids);
		close(pipe_out[READ]);
		dup2(pipe_out[WRITE], STDOUT_FD);
		close(pipe_out[WRITE]);
		exec_cmd(cmd, envp);
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

int	process_pipes(t_cmd *cmd, int *fd_in, char **envp, int *pids)
{
	int		pid;
	int		pipe_out[2];

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
		exec_cmd(cmd, envp);
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

int	process_last(t_cmd *cmd, int fd_in, char **envp, int *pids)
{
	int		fd_out;
	int		pid;

	fd_out = 0;
	pid = fork();
	if (pid == 0)
	{
		free(pids);
		dup2(fd_in, STDIN_FD);
		close(fd_in);
		exec_cmd(cmd, envp);
	}
	if (pid == -1)
		perror("minishell: process_last: fork");
	close(fd_in);
	return (pid);
}
