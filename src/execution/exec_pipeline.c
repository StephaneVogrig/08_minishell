/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:57:22 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/04 13:50:48 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_pipeline.h"

static t_bool	exec_pipe(t_cmd *cmdlist, t_env **env)
{
	int	fdin;

	fdin = 0;
	while (cmdlist)
	{
		cmdlist->pid = process(cmdlist, &fdin, env);
		if (cmdlist->pid == -1)
			return (FAILURE);
		cmdlist = cmdlist->next;
	}
	return (SUCCESS);
}

static int	exec_alone(t_cmd_m *cmd, t_env **env)
{
	t_builtin	builtin;
	int			exit_code;

	exit_code = 0;
	if (argv_expand(&cmd->argv, *env) == FAILURE)
	{
		cmd_free(cmd);
		return (EXIT_FAILURE);
	}
	builtin = builtin_function(cmd->argv);
	if (builtin)
		return (exec_builtin_alone(builtin, cmd, env));
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (exec_redir(cmd->redir, *env) != SUCCESS)
			exit_on_failure(cmd, NULL, NULL, *env);
		exec_cmd(cmd, env);
	}
	if (cmd->pid == -1)
		exit_on_failure(cmd, NULL, NULL, *env);
	exit_code = wait_process(cmd);
	cmd_free(cmd);
	return (exit_code);
}

int	exec_pipeline(t_cmd_m *pipeline, t_env **env)
{
	int		exit_code;

	if (!pipeline->next)
		return (exec_alone(pipeline, env));
	if (exec_pipe(pipeline, env) == FAILURE)
	{
		wait_process(pipeline);
		exit_code = EXIT_FAILURE;
	}
	else
		exit_code = wait_process(pipeline);
	pipeline_free(&pipeline);
	return (exit_code);
}
