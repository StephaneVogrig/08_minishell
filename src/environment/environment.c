/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:59:17 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/18 21:00:03 by smortemo         ###   ########.fr       */
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

t_env	*env_node_new(char *name, char *value, int type)
{
	t_env	*new;

	new = malloc(sizeof(*new));
	if (!new)
	{
		perror("minishell: env_node_new0");
		return (NULL);
	}
	new->name = ft_strdup(name);
	if (!new->name)
	{
		perror("minishell: env_node_new");
		free(new);
		return (NULL);
	}
	new->value = ft_strdup(value);
	if (!new->value)
	{
		perror("minishell: env_node_new");
		free(new->name);
		free(new);
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
