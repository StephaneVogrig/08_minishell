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

void	test(char **envp)
{
	// printf("--------------------------------------------\n");
	// printf("EXPORT ALONE \n");
	// printf("--------------------------------------------\n");
	export_alone(envp);
}

void	builtin_export_alone_test(char **strtab)
{
	// char *strtab[] = {"IIIIIIIIIIIIII", "zzzz=!!!", "ZZZZ=un", "cccc=export",
	// 	"bbbb=de", "AAAA=ceci", "LLLL=est", "aaaa=test", "ffff=seul",
	// 	"_=do not display", NULL};

	char **tab_malloc;
	tab_malloc = env_dup(strtab);

	// printf("--------------------------------------------\n");
	// printf("SOURCE TAB  \n");
	// printf("--------------------------------------------\n");
	// strtab_print(tab_malloc);
	test(tab_malloc);

	strtab_free(tab_malloc);
	// printf("____________________________________________\n");
	// printf("____________________________________________\n");
}