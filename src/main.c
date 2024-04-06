/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:55:55 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/06 19:06:54 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec_input.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	if (argc || argv || envp){};	
	signal(SIGINT, handler_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline(PROMPT_MINISHELL);
		if (!input)
			break;
		if (ft_strncmp("exit", input, 4) == 0)
		{
			free(input);
			write(1, "exit\n", 5);
			break;
		}
		if (*input)
		{
			add_history(input);
			exec_input(input);	
		}
		free(input);
	}		
	return (EXIT_SUCCESS);
}
