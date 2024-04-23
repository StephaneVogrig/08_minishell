/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:21:17 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/10 23:47:44 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unitest.h"

static char	**test(char **env, char *str)
{
	char	**tab;

	printf("--------------------------------------------\n");
	printf("TEST-> unset %s \n", str);
	printf("--------------------------------------------\n");
	env = builtin_unset(env, str);
	strtab_print(env);
	return (env);
}

void	builtin_unset_test(void)
{
	char *strtab[] = {"KEY=ceci", "KEY1=est", "KEY2=un", "KEY3=test", "KEY=de",
		"KEY4=unset", "KEY5=", NULL};

	char **tab_malloc;
	tab_malloc = env_dup(strtab);

	printf("\nSOURCE TAB ----------------------------------\n");
	strtab_print(tab_malloc);
	test(tab_malloc, NULL);
	tab_malloc = test(tab_malloc, "NOEXIST");
	tab_malloc = test(tab_malloc, "");
	tab_malloc = test(tab_malloc, NULL);
	tab_malloc = test(tab_malloc, "KEY1");
	tab_malloc = test(tab_malloc, "KEY3");
	tab_malloc = test(tab_malloc, "KEY");
	tab_malloc = test(tab_malloc, "NOEXIST2");
	tab_malloc = test(tab_malloc, "KEY5");
	tab_malloc = test(tab_malloc, "KEY2");
	tab_malloc = test(tab_malloc, "KEY4");
	strtab_free(tab_malloc);
	test(NULL, NULL);
	printf("____________________________________________\n");
	printf("____________________________________________\n");
}