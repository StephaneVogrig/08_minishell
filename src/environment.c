/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:59:17 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/05 14:03:59 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env	*env_dup(char **envp)
{
	t_env	*env;
	t_env	*node;
	int		i;

	// printf("ENV ********\n");
	// strtab_print(envp);
	// printf("************\n");
	if (!envp)
		return (NULL);
	i = 0;
	env = NULL;
	while (envp[i])
	{
		node = malloc(sizeof(*node));
		if (!node)
		{
			env_free(env);
			return (NULL);
		}
		node_init(node, envp[i], EXPORTED);
		lst_add_back(&env, node);
		i++;
	}
	node_HOME_cpy(env); // pour le ~
	return (env);
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
		if (!ft_strncmp(env->name, str, n))
			if (!*(env->name + n))
				return (env->value);
		env = env->next;
	}
	return (NULL);
}

// int	env_size_envp(t_env *env)
// {
// 	int	i;

// 	i = 0;
// 	while (env)
// 	{
// 		if (env->type == EXPORTED)
// 			i++;
// 		env = env->next;
// 	}
// 	return (i);
// }

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

	envp = calloc(env_lst_size(env, EXPORTED) + 1, sizeof(*envp));
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
