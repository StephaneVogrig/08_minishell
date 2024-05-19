/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:39:44 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/19 22:17:36 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_bool	env_shlvl_init(t_env **env)
{
	t_env *node;
	char *value;
	int num;
	char *new;

	node = env_get_node_n(*env, "SHLVL", 5);
	if (!node)
		return (node_init(node, "SHLVL=1"));
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
