/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:59:17 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/30 01:22:26 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	env_node_free(t_env *node)
{
	free(node->name);
	free(node->value);
	free(node);
}

void	env_node_del(t_env **env, t_env *node)
{
	t_env	*temp;
	t_env	*to_del;

	if (node == *env)
	{
		*env = node->next;
		env_node_free(node);
		return ;
	}
	temp = *env;
	while (temp->next && temp->next != node)
		temp = temp->next;
	if (temp->next)
	{
		to_del = temp->next;
		temp->next = to_del->next;
		env_node_free(to_del);
	}
}

void	env_free(t_env *env)
{
	t_env	*current;
	t_env	*temp;

	current = env;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		env_node_free(temp);
	}
}

void	display_the_list(t_env *env)
{
	while (env != NULL)
	{
		printf("%s=", env->name);
		printf("%s\n", env->value);
		env = env->next;
	}
}

t_bool	env_init(t_env *node, char *str)
{
	int	index;

	// printf("str= %s \n", str);
	index = ft_strchr_i(str, '=');
	node->name = ft_strndup(str, index);
	if (!node->name)
		return (FAILURE);
	node->value = ft_strdup(&str[index + 1]);
	if (!node->value)
		return (FAILURE);
	node->type = EXPORTED;
	node->next = NULL;
	// printf("node->name= %s, value= %s\n", node->name, node->value);
	return (SUCCESS);
}

void	env_add_back(t_env **env, t_env *node)
{
	t_env	*temp;

	if (!*env)
	{
		*env = node;
		return ;
	}
	temp = *env;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
}

t_env	*env_dup(char **envp)
{
	t_env	*env;
	t_env	*node;
	int		i;

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
		env_init(node, envp[i]);
		env_add_back(&env, node);
		i++;
	}
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

t_env	*env_get_node(t_env *env, char *str)
{
	if (!env || !str)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->name, str))
			return (env);
		env = env->next;
	}
	return (NULL);
}


int	env_size_envp(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->type == EXPORTED)
			i++;
		env = env->next;
	}
	return (i);
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
	// ft_printf("%s=%s ->%s\n", name, value, str);
	return (str);
}

/// transforme la liste en tableau
char	**env_to_envp(t_env *env)
{
	char	**envp;
	char	**temp;
	char	*str;

	envp = calloc(env_size_envp(env) + 1, sizeof(*envp));
	if (!envp)
		return (NULL);
	temp = envp;
	while (env)
	{
		if (env->type == EXPORTED)
		{
			str = env_join(env->name, env->value);
			//printf("strjoin-> %s\n", str);
			if (!str)
			{
				strtab_free(temp);
				return (NULL);
			}
			*temp++ = str;
		}
		env = env->next;
	}
	// strtab_print(envp);
	return (envp);
}
