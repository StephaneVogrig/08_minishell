/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:55:55 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/16 21:58:05 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_scan(t_env *env, int *exit_status)
{
	char	*input;

	while (1)
	{
		write(2, "\033[33mminishell>\033[0m", 20);
		input = readline("");
		g_signal = 0;
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
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int		exit_status;

	exit_status = 0;
	if (!argv)
		argc = argc + 0;
	if (argc > 1)
	{
		write(STDOUT_FD, "usage: ./minishell\n", 20);
		return (EXIT_SUCCESS);
	}
	signal(SIGINT, handler_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	env = env_dup(envp);
	init_shlvl(env);
	node_home_cpy(env);
	if (!env)
		return (EXIT_FAILURE);
	minishell_scan(env, &exit_status);
	env_free(env);
	close(0);
	write(1, "exit\n", 5);
	return (exit_status);
}
