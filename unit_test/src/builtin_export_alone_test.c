/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_alone_test.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:04:37 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/01 22:57:29 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unitest.h"

void	test_export_alone(t_env *envp)
{
	printf("--------------------------------------------\n");
	printf("EXPORT ALONE \n");
	printf("--------------------------------------------\n");
	display_envp_sorted(envp);
}

void	builtin_export_alone_test(void)
{
	char *strtab[] = {"z=!!!", "ZZZ=un", "cccc=export", "b=de", "AA=ceci",
		"LLLL=est", "_w=vrai", "aaaa=test", "uuuu=seul", "_=do not display",
		NULL};

	t_env *tab;
	tab = env_dup(strtab);

	export(tab, "alone1");
	export(tab, "alone2");

	// export(tab, "XXXXXX=---");

	printf("--------------------------------------------\n");
	printf("SOURCE LIST  \n");
	printf("--------------------------------------------\n");
	display_the_list(tab, ALL);

	test_export_alone(tab);

	env_free(tab);
	// printf("____________________________________________\n");
	// printf("____________________________________________\n");
}