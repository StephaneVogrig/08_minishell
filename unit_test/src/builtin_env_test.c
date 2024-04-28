/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:21:17 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/28 22:04:30 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unitest.h"

static char	**test(char **env)
{
	char	**tab;

	printf("--------------------------------------------\n");
	printf("TEST-> env \n");
	printf("--------------------------------------------\n");
	builtin_env(env);
	return (env);
}

void	builtin_env_test(void)
{
	char *strtab[] = {"KEY=ceci", "KEY1=est", "Do_not_display", "KEY2=un", "KEY3=test", "KEY=de",
		"KEY4=env", "KEY5=", NULL};

	t_env *strdup;
	strdup = env_dup(strtab);

	printf("\nSOURCE TAB ----------------------------------\n");
	strtab_print(strdup);
	test(strdup);
	strtab_free(strdup);
	// test(NULL);
	printf("____________________________________________\n");
	printf("____________________________________________\n");
}