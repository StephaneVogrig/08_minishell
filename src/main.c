/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:55:55 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/03 19:00:14 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;

	
	while (1)
	{
		// print_prompt();
		input = readline("");
		if (!input)
		{
			perror("minishell: readline");
			exit(1);
		}
		// add_history(input);
		// printf("%s", input);
		// printf("\n");
		if (ft_strncmp("exit", input, 4) == 0)
		{
			free(input);
			exit(0);
		}
		free(input);
	}
	return (0);
}