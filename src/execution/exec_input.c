/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:36:43 by stephane          #+#    #+#             */
/*   Updated: 2024/05/19 17:26:08 by svogrig          ###   ########.fr       */
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
		return (FAILURE);
	return (SUCCESS);
}

void	process_exec_cmd(t_cmd_m *cmd, t_env *env)
{
	if (!exec_redir(cmd->redir))
		exit_on_failure(cmd, NULL, NULL, env);
	exec_cmd(cmd, env);
}

int	exec_alone(t_cmd_m *cmd, t_env *env)
{
	pid_t		pid[2];
	t_builtin	builtin;
	int			exit_code;

	exit_code = 0;
	builtin = builtin_function(cmd->argv);
	if (builtin)
	{
		exit_code = exec_builtin_alone(builtin, cmd, env);
		cmd_free(cmd);
		return (exit_code);
	}
	pid[1] = 0;
	*pid = fork();
	if (*pid == 0)
		process_exec_cmd(cmd, env);
	if (*pid == -1)
	{
		cmd_free(cmd);
		env_free(env);
		exit(EXIT_FAILURE);
	}
	cmd_free(cmd);
	return (wait_process(pid));
}

int	exec_pipe(t_cmd_m *pipeline, t_env *env)
{
	pid_t	*pids;
	int		exit_code;

	pids = ft_calloc(sizeof(int), cmd_nbr(pipeline) + 1);
	if (!pids)
	{
		perror("minishell: exec_input: ft_calloc");
		pipeline_free(&pipeline);
		env_free(env);
		exit(EXIT_FAILURE);
	}
	exec_pipeline(pipeline, pids, env);
	pipeline_free(&pipeline);
	exit_code = wait_process(pids);
	free(pids);
	return (exit_code);
}

t_bool	is_empty(char *str)
{
	while (is_blank(*str))
		str++;
	if (*str == '\0')
		return (TRUE);
	return (FALSE);
}

int	exec_input(t_char_m *input, t_env *env)
{
	t_cmd_m	*pipeline;
	char	*str;

	str = skip_blank(input);
	if (*str == '\0')
	{
		free(input);
		return (EXIT_SUCCESS);
	}
	if (syntax_error(str))
	{
		free(input);
		return (SYNTAX_ERROR);
	}
	errno = 0;
	pipeline = input_to_pipeline(str, env);
	free(input);
	if (errno != 0)
		exit_on_failure(NULL, NULL, NULL, env);
	if (!pipeline || heredoc(pipeline, env) != SUCCESS)
		return (EXIT_SUCCESS);
	signal(SIGINT, handler_ctrl_c);
	if (!pipeline->next)
		return (exec_alone(pipeline, env));
	else
		return (exec_pipe(pipeline, env));
}
