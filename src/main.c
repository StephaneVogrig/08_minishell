/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:55:55 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/18 20:16:29 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_interactive_mode(t_env *env, int *exit_status)
{
	char	*input;

	if (shell_mode_init_interactive(env) == FAILURE)
		return ;
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
		exec_input(input, env, exit_status);
	}
	write(2, "exit\n", 5);
}

char	*mini_readline(void)
{
	char	c;
	t_buff	buff;
	char	*str;
	int		n;

	buff_init(&buff);
	while (TRUE)
	{
		n = read(STDIN_FD, &c, 1);
		if (n < 1)
			return (NULL);
		if (c == '\n')
			break;
		if (buff_add_char(&buff, c) == FAILURE)
		{
			buff_clear(&buff);
			return (NULL);
		}
	}
	str = buff_to_str(&buff);
	buff_clear(&buff);
	return (str);
}

void	run_file_mode(t_env *env, int *exit_status)
{
	char	*input;

	if (shell_mode_init_file(env) == FAILURE)
		return ;
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
	env = env_init(envp);
	if (!env)
		return (EXIT_FAILURE);
	if (isatty(STDIN_FD))
		run_interactive_mode(env, &exit_status);
	else
		run_file_mode(env, &exit_status);
	env_free(env);
	return (exit_status);
}
