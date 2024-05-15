/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:36:43 by stephane          #+#    #+#             */
/*   Updated: 2024/05/15 12:48:02 by svogrig          ###   ########.fr       */
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
	pipeline = pipeline->next;
	while (pipeline->next && *pid > -1)
	{
		*(++pid) = process_pipes(pipeline, &fd, env, pids);
		pipeline = pipeline->next;
	}
	if (*pid > -1)
		*(++pid) = process_last(pipeline, fd, env, pids);
	if (*pid == -1)
		return (ERROR);
	return (SUCCESS);
}

void	exec_cmd_alone(t_cmd_m *cmd, t_env *env, int *exit_status)
{
	pid_t		pid[2];
	t_builtin	builtin;

	builtin = builtin_function(cmd->argv);
	if (builtin)
	{
		*exit_status = exec_builtin_alone(builtin, cmd, env);
		cmd_free(cmd);
		return ;
	}
	pid[1] = 0;
	*pid = fork();
	if (*pid == 0)
		exec_cmd(cmd, env);
	if (*pid == -1)
	{
		cmd_free(cmd);
		env_free(env);
		exit(EXIT_FAILURE);
	}
	*exit_status = wait_process(pid);
	cmd_free(cmd);
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
	pipeline_free(&pipeline);
	free(pids);
}

t_bool	is_empty(char *str)
{
	while (is_blank(*str))
		str++;
	if (*str == '\0')
		return (TRUE);
	return (FALSE);
}

void	exec_input(t_char_m *input, t_env *env, int *exit_status)
{
	t_cmd_m	*pipeline;
	char	*str;

	str = skip_blank(input);
	if (*str == '\0')
	{
		free(input);
		*exit_status = SUCCESS;
		return ;
	}
	if (syntax_error(str))
	{
		free(input);
		*exit_status = SYNTAX_ERROR;
		return ;
	}
	errno = 0;
	pipeline = input_to_pipeline(str, env, exit_status);
	free(input);
	if (errno != 0)
		exit_on_failure(NULL, NULL, NULL, env);
	if (!pipeline || heredoc(pipeline, env, exit_status) != SUCCESS)
		return ;
	if (!pipeline->next)
		exec_cmd_alone(pipeline, env, exit_status);
	else
		exec_cmd_pipe(pipeline, env, exit_status);
}
