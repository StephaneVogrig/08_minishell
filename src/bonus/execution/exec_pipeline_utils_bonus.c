/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 04:08:43 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/12 04:13:04 by svogrig          ###   ########.fr       */
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
												t_env **env, t_cmd *data)
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
		exit_minishell_bonus(data, *env);
	return (exit_code);
}

static int	exec_subshell(t_cmd *cmd, t_env **env, t_cmd_m *data)
{
	int			exit_code;

	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (exec_redir(cmd->redir, *env) != SUCCESS)
			exit_on_failure_bonus(data, *env);
		exit_code = exec_pipelist(cmd->pipelist, env, data);
		env_free(*env);
		pipelist_free(data);
		exit(exit_code);
	}
	if (cmd->pid == -1)
	{
		perror("minishell: exec_subshell: fork");
		exit_on_failure_bonus(data, *env);
	}
	return (wait_process(cmd));
}

int	exec_alone(t_cmd *cmd, t_env **env, t_cmd_m *data)
{
	t_builtin	builtin;
	int			exit_code;

	if (cmd->flag == SUB)
		return (exec_subshell(cmd, env, data));
	if (argv_expand(&cmd->argv, *env) == FAILURE)
		return (EXIT_FAILURE);
	builtin = builtin_function(cmd->argv);
	if (builtin)
		return (exec_builtin_alone_bonus(builtin, cmd, env, data));
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (exec_redir(cmd->redir, *env) != SUCCESS)
			exit_on_failure_bonus(data, *env);
		exec_cmd(cmd, env, data);
	}
	if (cmd->pid == -1)
		exit_on_failure_bonus(data, *env);
	exit_code = wait_process(cmd);
	return (exit_code);
}
