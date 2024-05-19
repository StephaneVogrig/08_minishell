/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:59:17 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/19 12:31:39 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

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

t_env	*env_init(char **envp)
{
	t_env	*env;
	t_env	*node;
	
	node = NULL;
	env = NULL;
	if (*envp)
	{
		env = envp_to_env(envp);
		if (!env)
			return (NULL);
	}
	if (env_shlvl_init(&env) == FAILURE || env_pwd_init(&env) == FAILURE)
	{
		env_free(env);
		return (NULL);
	}
	if (exit_status_init(&env) == FAILURE)
	{
		env_free(env);
		return (NULL);
	}
	node_home_cpy(env);
	return(env);
}

t_bool	env_node_set_value(char *value, t_env *node)
{
	char	*str;

	str = NULL;
	if (value)
	{
		str = ft_strdup(value);
		if (!str)
		{
			perror("minishell: env_node_set_value");
			return (FAILURE);
		}
	}
	if (node->value)
		free(node->value);
	node->value = str;
	return (SUCCESS);
}

t_env	*env_node_new(char *name, char *value, int type)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(*new));
	if (!new)
	{
		perror("minishell: env_node_new");
		return (NULL);
	}
	new->name = ft_strdup(name);
	if (!new->name)
	{
		perror("minishell: env_node_new");
		free(new);
		return (NULL);
	}
	if (env_node_set_value(value, new) == FAILURE)
	{
		env_node_free(new);
		return (NULL);
	}
	new->type = type;
	return (new);
}

t_env	*env_add_new(char *name, char *value, int type, t_env **env)
{
	t_env	*new;
	
	new = env_node_new(name, value, type);
	if(!new)
		return (NULL);
	env_add_back(env, new);
	return (new);
}
