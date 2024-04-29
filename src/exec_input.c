/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:36:43 by stephane          #+#    #+#             */
/*   Updated: 2024/04/29 20:47:08 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_input.h"

t_bool	syntax_error_msg(char c)
{
	if (c == '\0')
		fd_printf(STDERR_FD, "minishell: syntax error near unexpected token `newline'\n", c);
	else
		fd_printf(STDERR_FD, "minishell: syntax error near unexpected token `%c'\n", c);
	return (TRUE);
}

char	*next_token_pipe(char *str)
{
	while (is_blank(*str))
		str++;
	if (*str == '\0')
	{
		syntax_error_msg('\0');
		return (NULL);
	}
	return (str);
}

char	*next_token_redir(char *str)
{
	char	*ptr;

	ptr = str;
	str++;
	if (*ptr == *str)
		str++;
	while (is_blank(*str))
		str++;
	ptr = ft_strchr("|<> \t", *str);
	if (ptr)
	{
		syntax_error_msg(*ptr);
		return (NULL);
	}
	return (str);
}

char	*end_quote(char *str)
{
	char	quote;
ft_printf("quote = %c\n", *str);
	quote = *str;
	str++;
	while (*str)
	{
ft_printf("str = %c\n", *str);
		if (*str == quote)
			return (str);
		str++;
	}
ft_printf("quote 2 = %c\n", *str);
	syntax_error_msg('\0');
	return (NULL);
}

t_bool	syntax_error(char *input)
{
	if (*input == '|')
		return (syntax_error_msg('|'));
	while (*input)
	{
		if (*input == '|')
			input = next_token_pipe(input);
		else if (*input == '<' || *input == '>')
			input = next_token_redir(input);
		else if (*input == '\"' || *input == '\'')
			input = end_quote(input);
		if (!input)
			return (TRUE);
		input++;			
	}
	return (FALSE);
}

// t_bool	syntax_error(char *input)
// {
// 	if (*input == '|' || *(input + ft_strlen(input) - 1) == '|')
// 	{
// 		fd_printf(STDERR_FD, "bash: syntax error near \" | \"\n");
// 		return (TRUE);
// 	}
// 	return (FALSE);
// }

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

void exec_cmd_pipe(t_cmd_m *pipeline, t_env *env, int *exit_status)
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
	pipeline = input_to_pipeline(skip_blank(input), env, exit_status);
// print_pipeline(pipeline);
	free(input);
	if (!pipeline)
	{
		env_free(env);
		exit(EXIT_FAILURE);
	}
	if (!pipeline->next)
		exec_cmd_alone(pipeline, env, exit_status);
	else
		exec_cmd_pipe(pipeline, env, exit_status);
}
