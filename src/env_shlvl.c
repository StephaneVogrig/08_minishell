/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:39:44 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/05 14:15:57 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "environment.h"

void	init_shlvl(t_env *env)
{
	t_env *node;
	char *value;
	int num;
	char *new;

	node = env_get_node_n(env, "SHLVL", 5);
	if (!node)
	{
		export_new_node(env, "SHLVL=1", 5);
		return ;
	}
	value = node->value;
	num = ft_atoi(value) + 1;
	new = ft_itoa(num);
	free(node->value);
	node->value = ft_strdup(new);
	free(new);
	if (!value)
		return ;
}