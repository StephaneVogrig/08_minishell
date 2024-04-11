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

	char **strdup;
	strdup = env_dup(strtab);

	printf("\nSOURCE TAB ----------------------------------\n");
	strtab_print(strdup);
	test(strdup, NULL);
	strdup = test(strdup, "NOEXIST");
	strdup = test(strdup, "");
	strdup = test(strdup, NULL);
	strdup = test(strdup, "KEY1");
	strdup = test(strdup, "KEY3");
	strdup = test(strdup, "KEY");
	strdup = test(strdup, "NOEXIST2");
	strdup = test(strdup, "KEY5");
	strdup = test(strdup, "KEY2");
	strdup = test(strdup, "KEY4");
	strtab_free(strdup);
	test(NULL, NULL);
	printf("____________________________________________\n");
	printf("____________________________________________\n");
}