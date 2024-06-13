/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_alone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 01:40:56 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/13 04:39:39 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_alone.h"

int	exec_alone(t_cmd *cmd, t_env **env, t_cmd_m *data)
{
	t_builtin	builtin;

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
			exit_on_failure(cmd, NULL, NULL, *env);
		exec_cmd(cmd, env, data);
	}
	if (cmd->pid == -1)
	{
		perror("minishell: exec_alone: fork");
		return (EXIT_FAILURE);
	}
	return (wait_process(cmd));
}
