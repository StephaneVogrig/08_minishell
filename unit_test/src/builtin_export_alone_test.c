/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_alone_test.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:04:37 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/19 00:18:51 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unitest.h"

void	test_export(char **envp)
{
	// printf("--------------------------------------------\n");
	// printf("EXPORT ALONE \n");
	// printf("--------------------------------------------\n");
	export_alone(envp);
}

void	builtin_export_alone_test(void)
{
	char *strtab[] = {"z=!!!", "ZZZ=un", "cccc=export",
		"b=de", "tout", "AA=ceci", "LLLL=est", "_w=vrai", "aaaa=test", "uuuu=seul",
		"_=do not display", NULL};

	char **tab_malloc;
	tab_malloc = env_dup(strtab);

	// printf("--------------------------------------------\n");
	// printf("SOURCE TAB  \n");
	// printf("--------------------------------------------\n");
	// strtab_print(tab_malloc);
	test_export(tab_malloc);

	strtab_free(tab_malloc);
	// printf("____________________________________________\n");
	// printf("____________________________________________\n");
}