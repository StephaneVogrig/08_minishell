/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:55:55 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/17 22:03:56 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_interactive_mode(t_env *env, int *exit_status)
{
	char	*input;

	while (1)
	{
		signal(SIGINT, handler_ctrl_c_interactive);
		prompt_print();
		input = readline("");
		g_signal = 0;
		signal(SIGINT, SIG_IGN);
		if (!input)
			break ;
		if (!*input)
		{
			free(input);
			continue ;
		}
		add_history(input);
		exec_input(input, env, exit_status);
	}
	write(2, "exit\n", 5);
}

void	suppress_endl(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			*str = '\0';
		else
			str++;
	}
}

void	run_file_mode(t_env *env, int *exit_status)
{
	char	*input;

	while (1)
	{
		signal(SIGINT, handler_ctrl_c_file);
		input = get_next_line(STDIN_FD);
		if (!input)
			break ;
		if (g_signal)
		{
			free(input);
			env_free(env);
			exit(128 + SIGINT);
		}
		suppress_endl(input);
		exec_input(input, env, exit_status);
	}
}

int	main(int argc __attribute__((unused)), \
		char **argv __attribute__((unused)), char **envp)
{
	t_env	*env;
	int		exit_status;

	exit_status = 0;
	if (argc > 1)
	{
		write(STDOUT_FD, "usage: ./minishell\n", 20);
		return (EXIT_SUCCESS);
	}
	signal(SIGQUIT, SIG_IGN);
	env = env_dup(envp);
	init_shlvl(env);
	node_home_cpy(env);
	if (!env)
		return (EXIT_FAILURE);
	if (isatty(STDIN_FD))
		run_interactive_mode(env, &exit_status);
	else
		run_file_mode(env, &exit_status);
	env_free(env);
	return (exit_status);
}
