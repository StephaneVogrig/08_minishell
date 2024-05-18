/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:47:12 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/18 18:37:00 by smortemo         ###   ########.fr       */
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
