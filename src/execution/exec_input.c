/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:36:43 by stephane          #+#    #+#             */
/*   Updated: 2024/05/06 06:30:26 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_input.h"

int	exec_pipeline(t_cmd *pipeline, pid_t *pids, t_env *env)
{
	int		fd;
	pid_t	*pid;

	fd = 0;
	pid = pids;
	*pid = process_first(pipeline, &fd, env, pids);
	pipeline = pipeline_clear_first(pipeline);
	while (pipeline->next && *pid > -1)
	{
		*(++pid) = process_pipes(pipeline, &fd, env, pids);
		pipeline = pipeline_clear_first(pipeline);
	}
	if (*pid > -1)
	{
		*(++pid) = process_last(pipeline, fd, env, pids);
		cmd_free(pipeline);
	}
	if (*pid == -1)
		return (ERROR);
	return (SUCCESS);
}

void	exec_cmd_alone(t_cmd_m *cmd, t_env *env, int *exit_status)
{
	pid_t	pid[2];

	if (builtin_is_executed(cmd, env, exit_status))
	{
		cmd_free(cmd);
		return ;
	}
	pid[1] = 0;
	*pid = fork();
	if (*pid == 0)
	{
		exec_cmd(cmd, env);
		exit(EXIT_FAILURE);
	}
	cmd_free(cmd);
	if (*pid == -1)
	{
		env_free(env);
		exit(EXIT_FAILURE);
	}
	*exit_status = wait_process(pid);
}

void	exec_cmd_pipe(t_cmd_m *pipeline, t_env *env, int *exit_status)
{
	pid_t	*pids;

	pids = ft_calloc(sizeof(int), cmd_nbr(pipeline) + 1);
	if (!pids)
	{
		perror("minishell: exec_input: ft_calloc");
		pipeline_free(&pipeline);
		env_free(env);
		exit(EXIT_FAILURE);
	}
	exec_pipeline(pipeline, pids, env);
	*exit_status = wait_process(pids);
	free(pids);
}

void	exec_input(t_char_m *input, t_env *env, int *exit_status)
{
	t_cmd_m	*pipeline;

	if (syntax_error(input))
	{
		free(input);
		*exit_status = SYNTAX_ERROR;
		return ;
	}
	errno = 0;
	pipeline = input_to_pipeline(skip_blank(input), env, exit_status);
	free(input);
	if (errno != 0)
	{
		env_free(env);
		exit(EXIT_FAILURE);
	}
	if (!pipeline)
		return ;
	if (!pipeline->next)
		exec_cmd_alone(pipeline, env, exit_status);
	else
		exec_cmd_pipe(pipeline, env, exit_status);
}
