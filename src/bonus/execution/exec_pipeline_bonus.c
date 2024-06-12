/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:11:14 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/12 04:09:56 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_pipeline_bonus.h"

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
