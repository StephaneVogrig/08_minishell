/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:21:17 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/30 01:04:54 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unitest.h"

static void	test(char **env, char *str, char *expected)
{
	printf("\n++++++++++\n");
	strtab_print(env);
	printf("++++++++++\n");
	printf("key to search: %s\n", str);
	//	printf("%s\n", env_get(env, str));
	printf("---------------------------\n");
}

void	env_get_test(void)
{
	char *strtab[] = {"KEY=bonjour", "KEY=perdu", "KEY2=encore", "KEY3=", NULL};

	test(NULL, NULL, NULL);
	test(strtab, NULL, NULL);
	test(strtab, "NULL", NULL);
	test(strtab, "KEY", "bonjour");
	test(strtab, "KEY2", "encore");
	test(strtab, "KEY3", "");
	test(NULL, "KEY", "bonjour");
}