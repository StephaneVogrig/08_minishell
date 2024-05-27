/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:59:17 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/27 01:24:58 by smortemo         ###   ########.fr       */
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

t_bool env_init_shellvar(t_env **env)
{
	t_bool	success;

	success = env_shlvl_init(env);
	if (success)
		success = env_pwd_init(env);
	if (success)
		success = exit_status_init(env);
	if(node_home_cpy(*env) == ENOMEM)
		return(FAILURE);
	return (success);
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
	if (env_init_shellvar(&env) == FAILURE)
	{
		env_free(env);
		return (NULL);
	}
	return(env);
}

int	env_set_value(char *name, char *value, t_env *env)
{
	t_env	*node;

	node = env_get_node(env, name);
	if (!node)
		return (ENOEXIST);
	return (env_node_set_value(value, node));
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
