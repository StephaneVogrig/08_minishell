/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:59:17 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/12 23:30:58 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

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

void	env_free(t_env *env)
{
	t_env	*current;
	t_env	*temp;

	current = env;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		env_node_free(temp);
	}
}

int	env_set_value(char *name, char *value, t_env *env)
{
	t_env	*node;

	node = env_get_node(env, name);
	if (!node)
		return (ENOEXIST);
	if (env_node_set_value(value, node) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

t_env	*env_add_new(char *name, char *value, int type, t_env **env)
{
	t_env	*new;

	new = env_node_new(name, value, type);
	if (!new)
		return (NULL);
	env_add_back(env, new);
	return (new);
}
