/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:02:34 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/25 14:29:57 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env	*env_get_node_n(t_env *env, char *str, int n)
{
	if (!env || !str)
		return (NULL);
	while (env)
	{
		if (!ft_strncmp(env->name, str, n) && *(env->name + n) == '\0')
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*env_get_type(t_env *env, char *str, int type)
{
	if (!env || !str)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->name, str) && env->type == type)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*env_get(t_env *env, char *str)
{
	if (!env || !str)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->name, str))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*env_get_n(t_env *env, char *str, int n)
{
	if (!env || !str || n < 1)
		return (NULL);
	while (env)
	{
		if (ft_strncmp(env->name, str, n) == 0)
			if (*(env->name + n) == '\0')
				return (env->value);
		env = env->next;
	}
	return (NULL);
}
