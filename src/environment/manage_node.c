/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:09:56 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/18 15:44:24 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "environment.h"

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
	lst_add_back(&env, node);
	// printf("env->name %s \n", env->name);
	return (0);
}