/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:39:44 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/06 15:12:21 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
# include <errno.h>

void	init_shlvl(t_env *env)
{
	t_env *node;
	char *value;
	int num;
	char *new;

	node = env_get_node_n(env, "SHLVL", 5);
	if (!node)
	{
		if(export_new_node(env, "SHLVL=1", 5) == ENOMEM)
		{
			env_free(env);
			exit(EXIT_FAILURE);
		}
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