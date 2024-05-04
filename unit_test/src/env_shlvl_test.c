/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:50:40 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/04 18:28:26 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unitest.h"
#include <limits.h>

void	test(t_env *env)
{
	printf("--------------------------------------------\n");
	printf("TEST\n");
	printf("--------------------------------------------\n");
	init_shlvl(env);
	// printf("****** NEW ENV ***************\n");
	// display_the_list(env, ALL);
}

void	env_shlvl_test(char **env)
{
	(void)env;
	char *strtab[] = {"KEY3=value", "SHLVL=1", "KEY2=value", "HOME=value",
		NULL};

	// char *strtab_unset[] = {"KEY1=value", "KEY2=value", NULL};

	t_env *strdup;
	strdup = env_dup(strtab);

	printf("\nSOURCE TAB ----------------------------------\n");
	display_the_list(strdup, ALL);
	test(strdup);

	env_free(strdup);
	// printf("____________________________________________\n");
	// printf("\n TEST WITH ENV unset SHLVL  \n");
	// printf("____________________________________________\n");
	// printf("\nSOURCE TAB ----------------------------------\n");
	// strdup = env_dup(strtab_unset);
	// display_the_list(strdup, ALL);
	// // test(strdup, "..");
	// env_free(strdup);
	printf("____________________________________________\n");
	printf("____________________________________________\n");
}