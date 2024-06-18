/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_alone_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 04:08:43 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/18 17:17:11 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_alone.h"
#include "exec_pipelist_bonus.h"

static int	exec_subshell(t_cmd *cmd, t_env **env, t_cmd_m *data)
{
	int			exit_code;

	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (exec_redir(cmd->redir, *env) != SUCCESS)
			exit_on_failure(data, NULL, NULL, *env);
		exit_code = exec_pipelist(cmd->pipelist, env, data);
		minishell_free(data, NULL, NULL, *env);
		exit(exit_code);
	}
	if (cmd->pid == -1)
	{
		perror("minishell: exec_subshell: fork");
		return (EXIT_FAILURE);
	}
	return (wait_process(cmd));
}

int	exec_alone(t_cmd *cmd, t_env **env, t_cmd_m *data)
{
	t_builtin	builtin;

	if (cmd->flag & SUB)
		return (exec_subshell(cmd, env, data));
	if (argv_expand(&cmd->argv, *env) == FAILURE)
		return (EXIT_FAILURE);
	builtin = builtin_function(cmd->argv);
	if (builtin)
		return (exec_builtin_alone(builtin, cmd, env, data));
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (exec_redir(cmd->redir, *env) != SUCCESS)
			exit_on_failure(data, NULL, NULL, *env);
		exec_cmd(cmd, env, data);
	}
	if (cmd->pid == -1)
	{
		perror("minishell: exec_alone: fork");
		return (EXIT_FAILURE);
	}
	return (wait_process(cmd));
}
