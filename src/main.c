/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:55:55 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/23 14:31:28 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "exec_input.h"
#include "minishell.h"

void	run_minishell(char **env)
{
	char	*input;

	while (1)
	{
		input = readline("minishell>");
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
			exec_input(input, env);
			continue ;
		}
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;

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
	if (!env)
		return (EXIT_FAILURE);
	run_minishell(env);
	strtab_free(env);
	write(1, "exit\n", 5);
	return (EXIT_SUCCESS);
}
