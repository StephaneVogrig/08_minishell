/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:50:40 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/05 13:50:18 by smortemo         ###   ########.fr       */
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
	printf("****** NEW ENV ***************\n");
	display_the_list(env, ALL);
}

void	env_shlvl_test(char **env)
{
	(void)env;
	char *strtab[] = {"KEY3=value", "SHLVL=1", "HOME=path", NULL};

	char *strtab_unset[] = {"KEY1=value", "KEY2=value", "HOME=path", NULL};

	t_env *strdup;
	strdup = env_dup(strtab);
	t_env *strdup_unset;
	strdup_unset = env_dup(strtab_unset);

	printf("\nSOURCE TAB ----------------------------------\n");
	display_the_list(strdup, ALL);
	test(strdup);
	env_free(strdup);
	
	printf("____________________________________________\n");
	printf("\n TEST WITH ENV unset SHLVL  \n");
	printf("____________________________________________\n");
	printf("\nSOURCE TAB ----------------------------------\n");
	display_the_list(strdup_unset, ALL);
	test(strdup_unset);
	env_free(strdup_unset);
	printf("____________________________________________\n");
	printf("____________________________________________\n");
}