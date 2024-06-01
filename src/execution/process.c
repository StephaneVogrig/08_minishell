/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 04:15:23 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/31 16:19:13 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

void	exec_cmd_pipe(t_cmd *cmd, t_env **env)
{
	int			exit_code;
	t_builtin	builtin;

	if (exec_redir(cmd->redir, *env) != SUCCESS)
		exit_on_failure(cmd, NULL, NULL, *env);
	builtin = builtin_function(cmd->argv);
	if (!builtin)
		exec_cmd(cmd, env);
	exit_code = builtin(cmd, env);
	pipeline_free(&cmd);
	env_free(*env);
	exit(exit_code);
}

int	process_first(t_cmd *cmd, int *fd_out, t_env **env)
{
	int	pid;
	int	pipe_out[2];

	if (pipe_ms(pipe_out))
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_out[READ]);
		dup2(pipe_out[WRITE], STDOUT_FD);
		close(pipe_out[WRITE]);
		exec_cmd_pipe(cmd, env);
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

int	process_pipes(t_cmd *cmd, int *fd_in, t_env **env)
{
	int	pid;
	int	pipe_out[2];

	if (pipe_ms(pipe_out))
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		dup2(*fd_in, STDIN_FD);
		close(*fd_in);
		close(pipe_out[READ]);
		dup2(pipe_out[WRITE], STDOUT_FD);
		close(pipe_out[WRITE]);
		exec_cmd_pipe(cmd, env);
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

int	process_last(t_cmd *cmd, int fd_in, t_env **env)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(fd_in, STDIN_FD);
		close(fd_in);
		exec_cmd_pipe(cmd, env);
	}
	if (pid == -1)
		perror("minishell: process_last: fork");
	close(fd_in);
	return (pid);
}
