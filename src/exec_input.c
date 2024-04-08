/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:36:43 by stephane          #+#    #+#             */
/*   Updated: 2024/04/08 04:01:49 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "exec_input.h"

t_bool	syntax_error(char *input)
{
	if (*input == '|' || *(input + ft_strlen(input) - 1) == '|')
	{
		fd_printf(STDERR_FD, "bash: syntax error near \" | \"\n");
		return (TRUE);
	}
	return (FALSE);
}

int	exec_pipeline(t_cmd *pipeline, pid_t *pids, char **envp)
{
	int		fd;
	pid_t	*pid;

	fd = 0;
	pid = pids;
	*pid = process_first(pipeline, &fd, envp, pids);
	pipeline = pipeline_clear_first(pipeline);
	while (pipeline->next && *pid > -1)
	{
		*(++pid) = process_pipes(pipeline, &fd, envp, pids);
		pipeline = pipeline_clear_first(pipeline);
	}
	if (*pid > -1)
	{
		*(++pid) = process_last(pipeline, fd, envp, pids);
		cmd_free(pipeline);
	}
	if (*pid == -1)
		return (ERROR);
	return (SUCCESS);
}

int	exec_cmd_alone(t_cmd *cmd, char **envp)
{
	pid_t	pid[2];

	pid[1] = 0;
	*pid = fork();
	if (*pid == 0)
	{
		exec_cmd(cmd, envp);
		exit(EXIT_FAILURE);
	}
	cmd_free(cmd);
	if (*pid == -1)
		exit(EXIT_FAILURE);
	return (wait_process(pid));
}

int	exec_input(t_char_m *input, char **envp)
{
	t_cmd	*pipeline;
	int		exit_code;
	pid_t	*pids;

	if (syntax_error(input))
		return (SYNTAX_ERROR);
	pipeline = input_to_pipeline(skip_blank(input));
	free(input);
	if (!pipeline)
		exit(EXIT_FAILURE);
	if (!pipeline->next)
		return(exec_cmd_alone(pipeline, envp));
	pids = ft_calloc(sizeof(int), cmd_nbr(pipeline) + 1);
	if (!pids)
	{
		perror("minishell: exec_input: ft_calloc");
		pipeline_free(&pipeline);
		exit(EXIT_FAILURE);
	}
	exec_pipeline(pipeline, pids, envp);
	exit_code = wait_process(pids);
	free(pids);
	return (exit_code);
}
