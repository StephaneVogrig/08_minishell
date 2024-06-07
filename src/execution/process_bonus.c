/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:20:33 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/07 12:02:12 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_bonus.h"

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

#include "debug.h"

int	process(t_cmd *cmd, int *fd_in, t_env **env, t_cmd *tofree)
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
		// ft_printf("\nprocess\n");	
		// print_cmd(cmd);
		if (cmd->flag == SUB)
		{
			int	exit_code;

			exit_code = exec_pipelist(cmd->pipelist, env, tofree);
			pipelist_free(tofree);
			return (exit_code);
		}
		handle_pipe_child(fd_in, pipe_out, cmd);

		t_cmd	*cmd_cpy;
		cmd_cpy = cmd_new();
		cmd_cpy->redir = cmd->redir;
		cmd_cpy->argv = cmd->argv;
		cmd->redir = NULL;
		cmd->argv = NULL;
		pipelist_free(tofree);

		exec_cmd_pipe(cmd_cpy, env);
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
