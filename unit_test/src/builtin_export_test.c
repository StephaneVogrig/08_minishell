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

// static char	**test(char **env, char *str)
// {
// 	char	**tab;

// 	printf("--------------------------------------------\n");
// 	printf("TEST-> export %s \n", str);
// 	printf("--------------------------------------------\n");
// 	env = builtin_export(env, str);
// 	strtab_print(env);
// 	return (env);
// }

// void	builtin_export_test(void)
// {
// 	char *strtab[] = {"KEY=ceci", "KEY1=est", "KEY2=un", NULL};

// 	char **tab_malloc;
// 	tab_malloc = env_dup(strtab);

// 	printf("\nSOURCE TAB ----------------------------------\n");
// 	strtab_print(tab_malloc);
// 	tab_malloc = test(tab_malloc, "KEY3=test");
// 	tab_malloc = test(tab_malloc, "");
// 	tab_malloc = test(tab_malloc, "KEY4=****");
// 	tab_malloc = test(tab_malloc, "KEY4=de");
// 	tab_malloc = test(tab_malloc, "KEY5=export");
// 	tab_malloc = test(tab_malloc, "KEY6=");
// 	tab_malloc = test(tab_malloc, "KEY6========");
// 	tab_malloc = test(tab_malloc, "KEY6+=+++=+=+=+");
// 	tab_malloc = test(tab_malloc, "KEY6=valide");
// 	tab_malloc = test(tab_malloc, "KEY6+=???");
// 	tab_malloc = test(tab_malloc, "KEY6+= oui !");
// 	tab_malloc = test(tab_malloc, "KEY7++=");
// 	tab_malloc = test(tab_malloc, "KEY@=");
// 	tab_malloc = test(tab_malloc, "KEY!=");
// 	tab_malloc = test(tab_malloc, "KEY.=");
// 	tab_malloc = test(tab_malloc, "KEY_=-------");
// 	tab_malloc = test(tab_malloc, "KEYalone");
// 	tab_malloc = test(tab_malloc, "KEYalone= c'est fini");
// 	tab_malloc = test(tab_malloc, NULL);
// dans ce cas export_alone se lance-> affiche liste par ordre alpha-ascii
// 	strtab_free(tab_malloc);
// 	test(NULL, NULL);
// 	printf("____________________________________________\n");
// 	printf("____________________________________________\n");
// }

void	test_export(t_env *env, char *str)
{
	printf("--------------------------------------------\n");
	printf("TEST-> export %s \n", str);
	printf("--------------------------------------------\n");
	builtin_export(env, str);
	display_the_list(env);
}

void	builtin_export_test(void)
{
	char *strtab[] = {"KEY=ceci", "KEY1=est", "KEY2=un", NULL};

	t_env *lst;
	lst = env_dup(strtab);

	printf("\nSOURCE TAB ----------------------------------\n");
	display_the_list(lst);
	test_export(lst, "KEY3=test");
	test_export(lst, "");
	test_export(lst, "KEY4=****");
	test_export(lst, "KEY4=de");
	test_export(lst, "KEY5=export");
	test_export(lst, "KEY6=");
	test_export(lst, "KEY6========");
	test_export(lst, "KEY6+=+++=+=+=+");
	test_export(lst, "KEY6=va");
	test_export(lst, "KEY6+=lide");
	test_export(lst, "KEY6+=!!!!!");
	test_export(lst, "KEY7++=");
	test_export(lst, "KEY@="); // ajouter message erreur !!
	test_export(lst, "KEY!=");
	test_export(lst, "KEY.=");
	test_export(lst, "=");
	test_export(lst, "_=-------");
	test_export(lst, "KEY0=______");
	test_export(lst, "KEYalone");
	test_export(lst, NULL);
	// dans ce cas export_alone se lance-> affiche liste par ordre alpha-ascii
	env_free(lst);
	test_export(NULL, NULL);
	printf("____________________________________________\n");
	printf("____________________________________________\n");
}