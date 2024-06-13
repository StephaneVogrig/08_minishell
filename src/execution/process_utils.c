/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 01:16:58 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/13 04:45:29 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process_utils.h"

void	exec_cmd_pipe(t_cmd *cmd, t_env **env, t_cmd *data)
{
	int			exit_code;
	t_builtin	builtin;

	if (argv_expand(&cmd->argv, *env) == FAILURE)
		exit_on_failure(data, NULL, NULL, *env);
	builtin = builtin_function(cmd->argv);
	if (!builtin)
		exec_cmd(cmd, env, data);
	exit_code = builtin(cmd, env);
	minishell_free(data, NULL, NULL, *env);
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
