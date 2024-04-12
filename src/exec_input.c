/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:36:43 by stephane          #+#    #+#             */
/*   Updated: 2024/04/12 17:12:05 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "exec_input.h"

int	exec_pipeline(t_cmd *pipeline, pid_t *pids, t_char_m **env)
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

void	exec_cmd_pipe(t_cmd *pipeline, t_char_m **env, int *exit_status)
{
	pid_t	*pids;

	pids = ft_calloc(sizeof(int), cmd_nbr(pipeline) + 1);
	if (!pids)
	{
		perror("minishell: exec_input: ft_calloc");
		pipeline_free(&pipeline);
		strtab_free(env);
		exit(EXIT_FAILURE);
	}
	exec_pipeline(pipeline, pids, env);
	*exit_status = wait_process(pids);
	free(pids);
}

void	exec_cmd_alone(t_cmd *cmd, t_char_m **env, int *exit_status)
{
	pid_t	pid[2];

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
		strtab_free(env);
		exit(EXIT_FAILURE);
	}
	*exit_status = wait_process(pid);
}

void	exec_input(t_char_m *input, t_char_m **env, int *exit_status)
{
	t_cmd	*pipeline;
	// char	*temp;

	// temp = skip_blank(input);
	// if (*temp == '\0')
	// {
	// 	free(input);
	// 	return ;
	// }
	*exit_status = 0;
	pipeline = input_to_pipeline(input, exit_status);
	free(input);
	if (!pipeline)
	{
		strtab_free(env);
		exit(EXIT_FAILURE);
	}
	if (exit_status)
	{
		pipeline_free(&pipeline);
		return ;
	}
	// create heredocs
	if (!pipeline->next)
		exec_cmd_alone(pipeline, env, exit_status);
	else
		exec_cmd_pipe(pipeline, env, exit_status);
}
