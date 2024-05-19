/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:58:54 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/19 20:58:27 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_bool	exit_status_init(t_env **env)
{
	t_env	*node;
	char	*str;

	str = ft_calloc(12, 1);
	if (!str)
		return (FAILURE);
	node = env_node_new("?", NULL, INTERNAL);
	if (!node)
	{
		free(str);
		return (FAILURE);
	}
	*str = '0';
	node->value = str;
	env_add_back(env, node);	
	return (SUCCESS);
}

void	exit_status_set(int n, t_env *env)
{
	t_env		*node;
	char		*temp;

	node = env_get_node(env, "?");
	temp = si32_to_decstr_offset(node->value, n);
	*temp = '\0';
}

inline char	*exit_status_get_str(t_env *env)
{
	return (env_get(env, "?"));
}

inline int	exit_status_get_int(t_env *env)
{
	char	*str;

	str = env_get(env, "?");
	return (ft_atoi(str));
}
