/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:20:33 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/07 18:37:03 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_bonus.h"

void	exec_cmd_pipe(t_cmd *cmd, t_env **env, t_cmd *data)
{
	int			exit_code;
	t_builtin	builtin;

	if (exec_redir(cmd->redir, *env) != SUCCESS)
		exit_on_failure_bonus(data, *env);
	if (argv_expand(&cmd->argv, *env) == FAILURE)
		exit_on_failure_bonus(data, *env);
	builtin = builtin_function(cmd->argv);
	if (!builtin)
		exec_cmd(cmd, env, data);
	exit_code = builtin(cmd, env);
	pipelist_free(data);
	env_free(*env);
	exit(exit_code);
}

void	handle_pipe_child(int *fd_in, int pipe_out[2], t_cmd *cmd)
{
	if (cmd->previous != NULL)
	{
		dup2(*fd_in, STDIN_FD);
		close(*fd_in);
	}
	if (cmd->next)
	{
		close(pipe_out[READ]);
		dup2(pipe_out[WRITE], STDOUT_FD);
		close(pipe_out[WRITE]);
	}
}

void	handle_pipe_parent(int *fd_in, int pipe_out[2], t_cmd *cmd)
{
	if (cmd->previous != NULL)
		close(*fd_in);
	if (cmd->next)
	{
		close(pipe_out[WRITE]);
		*fd_in = pipe_out[READ];
	}
}

void	subshell(t_cmd *pipelist, t_env **env, t_cmd *data)
{
	int		exit_code;

	exit_code = exec_pipelist(pipelist, env, data);
	env_free(*env);	
	pipelist_free(data);
	exit(exit_code);
}

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
		if (cmd->flag == SUB)
			subshell(cmd->pipelist, env, data);
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
