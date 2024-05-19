/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:55:55 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/19 17:34:47 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_interactive_mode(t_env *env)
{
	char	*input;
	int		exit_code;

	exit_code = 0;
	if (shell_mode_init_interactive(env) == FAILURE)
		return (EXIT_FAILURE);
	while (1)
	{
		signal(SIGINT, handler_ctrl_c_interactive);
		input = readline("\001\033[33m\002minishell>\001\033[0m\002");
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
		exit_code = exec_input(input, env);
		exit_status_set(exit_code, env);
	}
	write(2, "exit\n", 5);
	return (exit_code);
}

int	run_file_mode(t_env *env)
{
	char	*input;

	if (shell_mode_init_file(env) == FAILURE)
		return (EXIT_FAILURE);
	rl_inhibit_completion = 1;
	while (TRUE)
	{
		signal(SIGINT, handler_ctrl_c_file);
		input = mini_readline();
		if (!input)
			break ;
		if (g_signal)
		{
			free(input);
			env_free(env);
			exit(128 + SIGINT);
		}
		exec_input(input, env);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc __attribute__((unused)), \
		char **argv __attribute__((unused)), char **envp)
{
	t_env	*env;
	int		exit_code;

	exit_code = 0;
	if (argc > 1)
	{
		write(STDOUT_FD, "usage: ./minishell\n", 20);
		return (EXIT_SUCCESS);
	}
	signal(SIGQUIT, SIG_IGN);
	env = env_init(envp);
	if (!env)
		return (EXIT_FAILURE);
	if (isatty(STDIN_FD))
		exit_code = run_interactive_mode(env);
	else
		exit_code = run_file_mode(env);
	env_free(env);
	return (exit_code);
}
