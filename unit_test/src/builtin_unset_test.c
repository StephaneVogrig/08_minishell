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

// void	free_list(t_env *env)
// {
// 	t_env	*current;
// 	t_env	*temp;

// 	current = env;
// 	while (current != NULL)
// 	{
// 		temp = current;
// 		current = current->next;
// 		free(temp->name);
// 		free(temp->value);
// 		free(temp);
// 	}
// }
void	test(t_env *env, char *str)
{
	printf("--------------------------------------------\n");
	printf("TEST-> unset %s \n", str);
	printf("--------------------------------------------\n");
	builtin_unset(env, str);
	display_the_list(env);
}

void	builtin_unset_test(void)
{
	char *strtab[] = {"KEY0=ceci", "KEY1=est", "KEY2=un", "KEY3=test", "KEY=de",
		"KEY4=unset", "KEY5=", NULL};

	t_env *lst;
	lst = env_dup(strtab);

	printf("\nSOURCE TAB ----------------------------------\n");
	display_the_list(lst);
	test(lst, NULL);
	test(lst, "NOEXIST");
	test(lst, "");
	test(lst, NULL);
	test(lst, "KEY1");
	test(lst, "KEY3");
	test(lst, "KEY");
	test(lst, "NOEXIST2");
	test(lst, "KEY5");
	test(lst, "KEY2");
	test(lst, "KEY4");
	env_free(lst);
	test(NULL, NULL);
	printf("____________________________________________\n");
	printf("____________________________________________\n");
}