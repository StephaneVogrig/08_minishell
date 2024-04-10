/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dup_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:49:50 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/10 22:38:37 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unitest.h"

static void	test(char **strtab)
{
	char	**new;

	printf("\ntest  ----------------------------\n");
	if (!strtab)
		return ;
	new = env_dup(strtab);
	if (!new)
	{
		perror("");
		return ;
	}
	strtab_print(new);
	strtab_free(new);
	printf("----------------------------------\n");
	return ;
}

void	env_dup_test(char **argv, char **envp)
{
	test(envp);
	test(argv);
	test(NULL);
}