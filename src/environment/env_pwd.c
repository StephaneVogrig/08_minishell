/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:02:40 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/01 14:17:52 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_bool	env_pwd_init(t_env **env)
{
	t_env	*node;
	char	*str;
	char	buffer[PATH_MAX];

	str = NULL;
	node = NULL;
	if (!env_get(*env, "PWD"))
	{
		str = ft_strjoin("PWD=", getcwd(buffer, PATH_MAX));
		if (!str)
			return (FAILURE);
		node = malloc(sizeof(*node));
		if (!node)
			return (FAILURE);
		node_init(node, str);
		env_add_back(env, node);
	}
	else
		return (env_set_value("PWD", getcwd(buffer, PATH_MAX), *env));
	return (SUCCESS);
}
