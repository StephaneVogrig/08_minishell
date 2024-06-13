/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:57:22 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/13 01:41:37 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_pipeline.h"

static t_bool	exec_pipe(t_cmd *cmdlist, t_env **env, t_cmd_m *data)
{
	int	fdin;

	fdin = 0;
	while (cmdlist)
	{
		cmdlist->pid = process(cmdlist, &fdin, env, data);
		if (cmdlist->pid == -1)
			return (FAILURE);
		cmdlist = cmdlist->next;
	}
	return (SUCCESS);
}

int	exec_pipeline(t_cmd *pipeline, t_env **env, t_cmd_m *data)
{
	int		exit_code;

	if (!pipeline->next)
		exit_code = exec_alone(pipeline, env, data);
	else if (exec_pipe(pipeline, env, data) == FAILURE)
	{
		wait_process(pipeline);
		exit_code = EXIT_FAILURE;
	}
	else
		exit_code = wait_process(pipeline);
	return (exit_code);
}
