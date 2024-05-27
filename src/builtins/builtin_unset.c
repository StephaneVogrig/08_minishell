/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:23 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/27 02:52:59 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	unset(t_env **env, char *str)
{
	t_env	*node;

	if (!str)
		return (0);
	node = env_get_node(*env, str);
	if (node)
	{
		if (node->type == EXPORTED || node->type == NO_VALUE)
			env_node_del(env, node);
	}
	return (0);
}

int	builtin_unset(t_cmd *cmd, t_env **env)
{
	t_list *argv;

	if (!env)
		return (0);
	argv = cmd->argv;
	argv = argv->next;
	while (argv)
	{
		unset(env, argv->content);
		argv = argv->next;
	}
	return (0);
}