/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:55:55 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 17:22:49 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_not_valid_input(char *input, t_env **env)
{
	if (!*input)
	{
		free(input);
		return (TRUE);
	}
	if (shell_mode_is_interactive(*env))
		add_history(input);
	if (is_empty(input))
	{
		free(input);
		return (TRUE);
	}
	return (FALSE);
}

int	run_interactive_mode(t_env **env)
{
	char	*input;
	int		exit_code;

	if (shell_mode_init_interactive(env) == FAILURE)
		return (EXIT_FAILURE);
	exit_code = EXIT_SUCCESS;
	while (1)
	{
		signal(SIGINT, handler_ctrl_c_interactive);
		input = readline("\001\033[33m\002minishell>\001\033[0m\002");
		if (g_signal)
		{
			exit_status_set(g_signal + 128, *env);
			g_signal = 0;
		}
		signal(SIGINT, SIG_IGN);
		if (!input)
			break ;
		if (is_not_valid_input(input, env))
			continue ;
		exit_code = exec_input(input, env);
		exit_status_set(exit_code, *env);
	}
	write(2, "exit\n", 5);
	return (exit_code);
}

int	run_file_mode(t_env **env)
{
	char	*input;
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	while (TRUE)
	{
		signal(SIGINT, handler_ctrl_c_file);
		input = mini_readline();
		if (g_signal)
		{
			if (input)
				free(input);
			input = NULL;
			exit_code = 128 + SIGINT;
			break ;
		}
		if (!input)
			break ;
		if (is_not_valid_input(input, env))
			continue ;
		exit_code = exec_input(input, env);
		exit_status_set(exit_code, *env);
	}
	return (exit_code);
}

int	main(int argc, char **argv __attribute__((unused)), char **envp)
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
	if (isatty(STDIN_FILENO))
		exit_code = run_interactive_mode(&env);
	else
		exit_code = run_file_mode(&env);
	env_free(env);
	return (exit_code);
}
