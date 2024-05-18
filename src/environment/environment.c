/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:59:17 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/18 17:21:19 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	*mem_env_node(t_env *node, t_env *env)
{

	node = malloc(sizeof(*node));
	if (!node)
	{
		env_free(env);
		return (NULL);//exit ??
	}
	return (node);

}
void	lst_add_back(t_env **env, t_env *node)
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

t_bool	node_init(t_env *node, char *str, int type)
{
	int	index;

	index = ft_strchr_i(str, '=');
	node->name = ft_strndup(str, index);
	if (!node->name)
		return (FAILURE);//exit ??
	node->value = ft_strdup(&str[index + 1]);
	if (!node->value)
		return (FAILURE);//exit ??
	node->type = type;
	node->next = NULL;
	return (SUCCESS);
}

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
		node = mem_env_node(node, env);
		node_init(node, envp[i], EXPORTED);
		lst_add_back(&env, node);
		i++;
	}
	return (env);
}

char	*env_get_type(t_env *env, char *str, int type)
{
	if (!env || !str)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->name, str) && env->type == type)
			return (env->value);
		env = env->next;
	}
	return (NULL);
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

void	env_node_free(t_env *node)
{
	free(node->name);
	free(node->value);
	free(node);
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
	char	*str;
	char buffer[PATH_MAX];
	
	env = NULL;
	node = NULL;
	if (!envp[0])
	{	
		node = mem_env_node(node, env);
		node_init(node, "SHLVL=1", EXPORTED);
		lst_add_back(&env, node);
	}
	else
	{
		env = envp_to_env(envp);
		init_shlvl(env);
	}
	if(!env_get_type(env, "PWD", EXPORTED))
	{
		node = mem_env_node(node, env);
		str = ft_strjoin("PWD=", getcwd(buffer, PATH_MAX));
		node_init(node, str, EXPORTED);
		lst_add_back(&env, node);
	}	
	node_home_cpy(env);
	return(env);
}
