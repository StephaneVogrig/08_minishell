/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:09:56 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/18 20:02:03 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "environment.h"

t_bool	node_init(t_env *node, char *str, int type)
{
	int	index;

	index = ft_strchr_i(str, '=');
	node->name = ft_strndup(str, index);
	if (!node->name)
		return (FAILURE);//exit ??
	node->value = ft_strdup(&str[index + 1]);
	if (!node->value)
		return (FAILURE);//exit ??
	node->type = type;
	node->next = NULL;
	return (SUCCESS);
}

void	env_node_free(t_env *node)
{
	free(node->name);
	free(node->value);
	free(node);
}

void	env_node_del(t_env **env, t_env *node)
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
t_bool	var_init(t_env *node, char *str, int n)
{
	node->name = mini_strndup(str, n);
	if (!node->name)
		return (FAILURE);
	if (str[n] != '\0')
	{
		node->value = mini_strdup(&str[n + 1]);
		if (!node->value)
			return (FAILURE);
		node->type = EXPORTED;
	}
	else
	{
		node->value = mem_malloc(1);
		if (!node->value)
			return (FAILURE);
		node->value[0] = '\0';
		node->type = NO_VALUE;
	}
	node->next = NULL;
	return (SUCCESS);
}

int	export_new_node(t_env *env, char *str, int n)
{
	t_env *node;

	node = mem_malloc(sizeof(*node));
	if (!node)
		return (ENOMEM);
	if (!var_init(node, str, n))
		return (ENOMEM);
	env_add_back(&env, node);
	return (0);
}
