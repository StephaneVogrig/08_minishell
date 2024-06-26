/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:31:06 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/27 14:36:37 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_bool	env_node_set_value(char *value, t_env *node)
{
	char	*str;

	str = NULL;
	if (value)
	{
		str = ft_strdup(value);
		if (!str)
		{
			perror("minishell: env_node_set_value");
			return (FAILURE);
		}
	}
	if (node->value)
		free(node->value);
	node->value = str;
	return (SUCCESS);
}

t_env	*env_node_new(char *name, char *value, int type)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(*new));
	if (!new)
	{
		perror("minishell: env_node_new");
		return (NULL);
	}
	new->name = ft_strdup(name);
	if (!new->name)
	{
		perror("minishell: env_node_new");
		free(new);
		return (NULL);
	}
	if (env_node_set_value(value, new) == FAILURE)
	{
		env_node_free(new);
		return (NULL);
	}
	new->type = type;
	return (new);
}
