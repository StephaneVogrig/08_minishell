/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:55:55 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/08 02:05:41 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_input.h"
#include "minishell.h"

void	run_minishell(char **envp)
{
	char	*input;
	int		exit_code;

	while (1)
	{
		input = readline(PROMPT_MINISHELL);
		if (!input)
			break ;
		if (ft_strncmp("exit", input, 4) == 0)
		{
			free(input);
			return ; ;
		}
		if (*input)
		{
			add_history(input);
			exit_code = exec_input(input, envp);
			continue ;
		}
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (!argv)
		argc = argc + 0;	
	if (argc > 1)
	{
		write(STDOUT_FD, "usage: ./minishell\n", 20);
		return (EXIT_SUCCESS);
	}
	signal(SIGINT, handler_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	run_minishell(envp);
	write(1, "exit\n", 5);
	return (EXIT_SUCCESS);
}
