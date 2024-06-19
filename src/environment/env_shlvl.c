/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:39:44 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/19 18:38:08 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_bool	node_shlvl(t_env **env)
{
	t_env	*node;

	node = mem_malloc(sizeof(*node));
	if (!node)
		return (FAILURE);
	env_add_back(env, node);
	if (node_init(node, "SHLVL=1") == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}

t_bool	env_shlvl_init(t_env **env)
{
	t_env	*node;
	char	*value;
	int		num;
	char	*new;

	node = env_get_node_n(*env, "SHLVL", 5);
	if (!node)
		return (node_shlvl(env));
	value = node->value;
	num = ft_atoi(value) + 1;
	if (num < 0)
		num = 0;
	new = ft_itoa(num);
	if (!new)
		return (FAILURE);
	free(node->value);
	node->value = ft_strdup(new);
	free(new);
	if (!value)
		return (FAILURE);
	return (SUCCESS);
}
