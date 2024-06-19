/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:54:58 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/19 18:46:48 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_bool	envp_to_env(char **envp, t_env **env)
{
	t_env	*node;
	int		i;

	i = 0;
	node = NULL;
	while (envp[i])
	{
		node = malloc(sizeof(*node));
		if (!node)
		{
			perror("minishell: envp_to_env: malloc");
			env_free(*env);
			return (FAILURE);
		}
		env_add_back(env, node);
		if (node_init(node, envp[i]) == FAILURE)
		{
			env_free(*env);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

// concatenates name and value in form "name=value"
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

// copy a list t_env in a tab of string
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
