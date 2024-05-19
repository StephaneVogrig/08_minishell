/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:54:58 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/19 16:13:45 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env	*envp_to_env(char **envp)
{
	t_env	*env;
	t_env	*node;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	node = NULL;
	env = NULL;
	while (envp[i])
	{
		node = malloc(sizeof(*node));
		if (!node)
		{
			env_free(env);
			return (NULL);
		}
		node_init(node, envp[i]);
		env_add_back(&env, node);
		i++;
	}
	return (env);
}

// cree un malloc qui contient "name=value"
char	*env_join(char *name, char *value)
{
	int		name_len;
	char	*str;
	char	*temp;

	name_len = ft_strlen(name);
	str = malloc(name_len + ft_strlen(value) + 2);
	if (!str)
		return (NULL);
	temp = str;
	if (name)
		temp = strcpy_offset(str, name);
	*temp++ = '=';
	if (value)
		temp = strcpy_offset(temp, value);
	*temp = '\0';
	return (str);
}

/// transforme la liste en tableau
char	**env_to_envp(t_env *env)
{
	char	**envp;
	char	**temp;
	char	*str;

	envp = calloc(env_size(env, EXPORTED) + 1, sizeof(*envp));
	if (!envp)
		return (NULL);
	temp = envp;
	while (env)
	{
		if (env->type == EXPORTED)
		{
			str = env_join(env->name, env->value);
			if (!str)
			{
				strtab_free(temp);
				return (NULL);
			}
			*temp++ = str;
		}
		env = env->next;
	}
	return (envp);
}
