/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:23 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/17 16:23:58 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "builtin.h"

static int	unset(t_env **env, char *str)
{
	t_env	*node;

	if (!str)
		return (EXIT_SUCCESS);
	node = env_get_node(*env, str);
	if (node)
	{
		if (node->type == EXPORTED || node->type == NO_VALUE)
			env_node_del(env, node);
		else if (node->type == DIR_ || node->type == DIR_NO_VAL)
			env_node_del(env, node);
	}
	return (EXIT_SUCCESS);
}

int	builtin_unset(t_cmd *cmd, t_env **env)
{
	t_list	*argv;

	if (!env)
		return (EXIT_SUCCESS);
	argv = cmd->argv;
	argv = argv->next;
	while (argv)
	{
		unset(env, argv->content);
		argv = argv->next;
	}
	return (EXIT_SUCCESS);
}
