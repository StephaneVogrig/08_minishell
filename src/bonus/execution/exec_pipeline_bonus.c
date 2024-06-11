/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:11:14 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/07 18:55:53 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_pipeline_bonus.h"

static void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

static void	exit_minishell_bonus(t_cmd *pipelist, t_env *env)
{
	int	exit_code;

	exit_code = exit_status_get_int(env);
	env_free(env);
	pipelist_free(pipelist);
	exit(exit_code);
}

static int	exec_builtin_alone_bonus(t_builtin builtin, t_cmd *cmd, \
												t_env **env, t_cmd *pipelist)
{
	int	fd[2];
	int	exit_code;

	fd[0] = dup(0);
	fd[1] = dup(1);
	exit_code = exec_redir(cmd->redir, *env);
	if (exit_code == FAILURE)
	{
		close_fd(fd);
		return (EXIT_FAILURE);
	}
	else if (exit_code == SUCCESS)
		exit_code = builtin(cmd, env);
	else
		exit_code = EXIT_FAILURE;
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close_fd(fd);
	if (builtin == &builtin_exit && exit_code < 0)
		exit_minishell_bonus(pipelist, *env);
	return (exit_code);
}

static t_bool	exec_pipe(t_cmd *pipeline, t_env **env, t_cmd *data)
{
	int	fdin;

	fdin = 0;
	while (pipeline)
	{
		pipeline->pid = process(pipeline, &fdin, env, data);
		if (pipeline->pid == -1)
			return (FAILURE);
		pipeline = pipeline->next;
	}
	return (SUCCESS);
}

static int	exec_alone(t_cmd_m *cmd, t_env **env, t_cmd *data)
{
	t_builtin	builtin;
	int			exit_code;

	if (cmd->flag == SUB)
		return (exec_pipelist(cmd->pipelist, env, data));
	exit_code = 0;
	if (argv_expand(&cmd->argv, *env) == FAILURE)
		return (EXIT_FAILURE);
	builtin = builtin_function(cmd->argv);
	if (builtin)
		return (exec_builtin_alone_bonus(builtin, cmd, env, data));
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (exec_redir(cmd->redir, *env) != SUCCESS)
			exit_on_failure_bonus(data, *env);
		exec_cmd(cmd, env, data);
	}
	if (cmd->pid == -1)
		exit_on_failure(cmd, NULL, NULL, *env);
	exit_code = wait_process(cmd);
	return (exit_code);
}

int	exec_pipeline(t_cmd_m *pipeline, t_env **env, t_cmd_m *data)
{
	int		exit_code;

	if (!pipeline->next)
		return (exec_alone(pipeline, env, data));
	if (exec_pipe(pipeline, env, data) == FAILURE)
	{
		wait_process(pipeline);
		exit_code = EXIT_FAILURE;
	}
	else
		exit_code = wait_process(pipeline);
	return (exit_code);
}
