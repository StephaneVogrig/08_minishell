/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:02:16 by stephane          #+#    #+#             */
/*   Updated: 2024/04/07 13:42:58 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

int	process_infile(t_cmd *cmd, int *pipe_out, char **envp, int *pids)
{
	int		fd;
	int		pid;
	
	fd = 0;
	pid = fork();
	if (pid == 0)
	{
		close(pipe_out[READ]);
		free(pids);
		dup2(pipe_out[WRITE], STDOUT_FD);
		close(pipe_out[WRITE]);
		exec_cmd(cmd, envp);
	}
	if (pid == -1)
		exit_pipex("minishell: process_infile: pipe", pids, pipe_out);
	close(pipe_out[WRITE]);

	return (pid);
}

int	process_pipes(t_cmd *cmd, int *fd_in, char **envp, int *pids)
{
	int		pid;
	int		pipe_out[2];

	if (pipe(pipe_out) == -1)
	{
		perror("miniishell: process_pipes: pipe");
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipe_out[READ]);
		free(pids);
		dup2(*fd_in, STDIN_FD);
		close(*fd_in);
		dup2(pipe_out[WRITE], STDOUT_FD);
		close(pipe_out[WRITE]);
		exec_cmd(cmd, envp);
	}
	if (pid == -1)
		perror("minishell: process_pipes: fork");
	close(*fd_in);
	close(pipe_out[WRITE]);
	*fd_in = pipe_out[READ];
	return (pid);
}

int	process_outfile(t_cmd *cmd, int fd_in, char **envp, int *pids)
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
		perror("minishell: process_outfile: fork");
	return (pid);
}
