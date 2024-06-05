/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 04:15:23 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/05 18:22:40 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

void	exec_cmd_pipe(t_cmd *cmd, t_env **env)
{
	int			exit_code;
	t_builtin	builtin;

	if (exec_redir(cmd->redir, *env) != SUCCESS)
		exit_on_failure(cmd, NULL, NULL, *env);
	if (argv_expand(&cmd->argv, *env) == FAILURE)
		exit_on_failure(cmd, NULL, NULL, *env);
	builtin = builtin_function(cmd->argv);
	if (!builtin)
		exec_cmd(cmd, env);
	exit_code = builtin(cmd, env);
	pipeline_free(&cmd);
	env_free(*env);
	exit(exit_code);
}

void	handle_pipe_child(t_bool need_pipeout, int *fd_in, int pipe_out[2], \
							t_cmd *cmd)
{
	if (cmd->previous != NULL)
	{
		dup2(*fd_in, STDIN_FD);
		close(*fd_in);
	}
	if (need_pipeout)
	{
		close(pipe_out[READ]);
		dup2(pipe_out[WRITE], STDOUT_FD);
		close(pipe_out[WRITE]);
	}
}

void	handle_pipe_parent(t_bool need_pipeout, int *fd_in, int pipe_out[2], \
							t_cmd *cmd)
{
	if (cmd->previous != NULL)
		close(*fd_in);
	if (need_pipeout)
	{
		close(pipe_out[WRITE]);
		*fd_in = pipe_out[READ];
	}
}

int	process(t_cmd *cmd, int *fd_in, t_env **env)
{
	int		pid;
	int		pipe_out[2];
	t_bool	need_pipeout;

	need_pipeout = cmd->next && cmd->next->flag == PIPE;
	if (need_pipeout)
		if (pipe_ms(pipe_out))
			return (-1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		handle_pipe_child(need_pipeout, fd_in, pipe_out, cmd);
		exec_cmd_pipe(cmd, env);
	}
	if (pid == -1)
	{
		perror("minishell: process_pipes: fork");
		if (need_pipeout)
			close(pipe_out[READ]);
	}
	handle_pipe_parent(need_pipeout, fd_in, pipe_out, cmd);
	return (pid);
}
