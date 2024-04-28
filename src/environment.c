/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:59:17 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/29 00:06:41 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	env_free(t_env *env)
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
void	display_the_list(t_env *env)
{
	while (env != NULL)
	{
		printf("%s = ", env->name);
		printf("%s\n", env->value);
		env = env->next;
	}
}

t_bool	env_init(t_env *node, char *str)
{
	int	index;

	// printf("str= %s \n", str);
	index = ft_strchr_i(str, '=');
	node->name = ft_strndup(str, index);
	if (!node->name)
		return (FAILURE);
	node->value = ft_strdup(&str[index + 1]);
	if (!node->value)
		return (FAILURE);
	node->type = EXPORTED;
	node->next = NULL;
	// printf("node->name= %s, value= %s\n", node->name, node->value);
	return (SUCCESS);
}

void	env_add_back(t_env **env, t_env *node)
{
	t_env	*temp;

	if (!*env)
	{
		*env = node;
		return ;
	}
	temp = *env;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
}

t_env	*env_dup(char **envp)
{
	t_env	*env;
	t_env	*node;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	env = NULL;
	while (envp[i])
	{
		// printf("envp[i]= %s \n", envp[i]);
		node = malloc(sizeof(*node));
		if (!node)
		{
			env_free(env);
			return (NULL);
		}
		env_init(node, envp[i]);
		// printf("node->name= %s, value= %s\n", node->name, node->value);
		env_add_back(&env, node);
		display_the_list(env);
		printf("----------\n");
		i++;
	}
	return (env);
}
/////// A ADAPTER /////
char	*env_get(char **env, char *str)
{
	int	size;

	if (!env || !str)
		return (NULL);
	size = ft_strlen(str);
	while (*env)
	{
		if (!ft_strncmp(*env, str, size))
			if (*(*env + size) == '=')
				return (*env + size + 1);
		env++;
	}
	return (NULL);
}

char	*env_get_n(char **env, char *str, int n)
{
	if (!env || !str || n < 1)
		return (NULL);
	while (*env)
	{
		if (!ft_strncmp(*env, str, n))
			if (*(*env + n) == '=')
				return (*env + n + 1);
		env++;
	}
	return (NULL);
}
