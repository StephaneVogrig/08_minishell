/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:47:12 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/19 22:07:49 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

int	env_size(t_env *env, int type)
{
	int	i;

	i = 0;
	if (type == ALL)
	{
		while (env)
		{
			if (env->type == EXPORTED || env->type == NO_VALUE)
				i++;
			env = env->next;
		}
	}
	else if (type == EXPORTED)
	{
		while (env)
		{
			if (env->type == EXPORTED)
				i++;
			env = env->next;
		}
	}
	return (i);
}

void	env_display(t_env *env, int type)
{
	if (type == ALL)
	{
		while (env != NULL)
		{
			printf("%s=", env->name);
			printf("%s\n", env->value);
			env = env->next;
		}
	}
	if (type == EXPORTED)
	{
		while (env != NULL)
		{
			if (env->type == EXPORTED)
			{
				printf("%s=", env->name);
				printf("%s\n", env->value);
			}
			env = env->next;
		}
	}
}

static t_bool	env_init_shellvar(t_env **env)
{
	t_bool	success;

	success = env_shlvl_init(env);
	if (success)
		success = env_pwd_init(env);
	if (success)
		success = exit_status_init(env);
	if (success && node_home_cpy(*env) == ENOMEM)
		return (FAILURE);
	return (success);
}

t_env	*env_init(char **envp)
{
	t_env	*env;

	env = NULL;
	if (*envp)
	{
		if (envp_to_env(envp, &env) == FAILURE)
			return (NULL);
	}
	if (env_init_shellvar(&env) == FAILURE)
	{
		env_free(env);
		return (NULL);
	}
	return (env);
}
