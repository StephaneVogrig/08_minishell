/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dup_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:49:50 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/30 01:11:07 by smortemo         ###   ########.fr       */
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

// void	display_list(t_env *env)
// {
// 	t_env	*current;

// 	current = env;
// 	while (current != NULL)
// 	{
// 		printf("%s = ", env->name);
// 		printf("%s\n", env->value);
// 		current = current->next;
// 	}
// }

static void	test(char **strtab)
{
	t_env	*new;

	printf("\ntest  ----------------------------\n");
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
	display_list(new);
	free_link_list(new);
	printf("----------------------------------\n");
	return ;
}

void	env_dup_test(char **argv, char **envp)
{
	test(envp);
	// test(argv);
	// test(NULL);
}