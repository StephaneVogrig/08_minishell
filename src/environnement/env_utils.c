/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:59:17 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/06 14:48:46 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

char	*create_HOME_path(t_env *env)
{
	char	*str;
	int		index;
	char	*home;

	str = env_get(env, "PWD");
	if (!str)
		return(NULL);
	index = ft_strstr(str, "/nfs/homes/");
	while (str[index] != '/')
		index++;
	home = ft_strndup(str, index + 1);
	return (home);
}

void	node_HOME_cpy(t_env *env)
{
	t_env	*node;
	char	*str;

	node = malloc(sizeof(*node));
	if (!node)
		return ;
	node->name = ft_strdup("HOME_cpy");
	if (!node->name)
		return ;
	str = env_get(env, "HOME");
	if (str)
		node->value = ft_strdup(str);
	else
		node->value = create_HOME_path(env);
	node->type = INTERNAL;
	node->next = NULL;
	lst_add_back(&env, node);
	return ;
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
