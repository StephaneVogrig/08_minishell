/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dup_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:49:50 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/18 19:31:04 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unitest.h"

// static void	test(char **strtab)
// {
// 	char	**new;

// 	printf("\ntest  ----------------------------\n");
// 	if (!strtab)
// 		return ;
// 	new = env_dup(strtab);
// 	if (!new)
// 	{
// 		perror("");
// 		return ;
// 	}
// 	strtab_print(new);
// 	strtab_free(new);
// 	printf("----------------------------------\n");
// 	return ;
// }

void	free_link_list(t_env *env)
{
	t_env	*current;
	t_env	*temp;

	current = env;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

void	display_list(t_env *env)
{
	while (env != NULL)
	{
		printf("%s = ", env->name);
		printf("%s\n", env->value);
		env = env->next;
	}
}

static void	test(char **strtab)
{
	t_env	*new;

	if (!strtab)
		return ;
	strtab_print(strtab);
	printf("----------------------------------\n");
	new = env_dup(strtab);
	if (!new)
	{
		perror("");
		return ;
	}
	env_shlvl_init(new); //initialise valeur SHLVL
	node_home_cpy(new); // pour ~
	display_list(new);
	free_link_list(new);
	printf("----------------------------------\n");
	return ;
}

void	env_dup_test(char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	char *strtab[] = {"KEY3=value", "SHLVL=1", "HOME=path", "SHLVL=1", NULL};
	char *strtab_unset[] = {"KEY1=value", "KEY2=value", NULL};
	printf("\n TEST ENV ----------------------------------\n");
	test(strtab);
	printf("\n TEST ENV unset HOME & SHLVL ---------------\n");
	test(strtab_unset);
	printf("\n TEST ENV == NULL---------------------------\n");
	test(NULL);
	
	// test(NULL);
}