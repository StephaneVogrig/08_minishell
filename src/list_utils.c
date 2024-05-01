/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:47:12 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/01 22:33:04 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env	*env_get_node_n(t_env *env, char *str, int n)
{
	if (!env || !str)
		return (NULL);
	while (env)
	{
		if (!ft_strncmp(env->name, str, n))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	lst_node_del(t_env **env, t_env *node)
{
	t_env	*temp;
	t_env	*to_del;

	if (node == *env)
	{
		*env = node->next;
		env_node_free(node);
		return ;
	}
	temp = *env;
	while (temp->next && temp->next != node)
		temp = temp->next;
	if (temp->next)
	{
		to_del = temp->next;
		temp->next = to_del->next;
		env_node_free(to_del);
	}
}

int	env_lst_size(t_env *env, int type)
{
	int	i;

	i = 0;
	if (type == ALL)
	{
		while (env)
		{
			i++;
			env = env->next;
		}
	}
	else if (type == EXPORTED)
	{
		while (env)
		{
			if (env->type == EXPORTED)
				i++;
			env = env->next;
		}
	}
	return (i);
}

void	display_the_list(t_env *env, int type)
{
	if (type == ALL)
	{
		while (env != NULL)
		{
			printf("%s=", env->name);
			printf("%s\n", env->value);
			env = env->next;
		}
	}
	if (type == EXPORTED)
	{
		while (env != NULL)
		{
			if (env->type == EXPORTED)
			{
				printf("%s=", env->name);
				printf("%s\n", env->value);
			}
			env = env->next;
		}
	}
}

void	lst_add_back(t_env **env, t_env *node)
{
	t_env *temp;

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