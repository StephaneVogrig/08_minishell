/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:59:17 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/18 18:29:00 by smortemo         ###   ########.fr       */
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
	char	*str;
	char buffer[PATH_MAX];
	
	env = NULL;
	node = NULL;
	// + exist_status "?"
	if (!envp[0])
	{	
		// init_shlvl(env);
		node = mem_env_node(node, env);
		node_init(node, "SHLVL=1", EXPORTED);//protection
		env_add_back(&env, node);
	}
	else
	{
		env = envp_to_env(envp);
		init_shlvl(env);
	}
	if(!env_get_type(env, "PWD", EXPORTED))
	{
		node = mem_env_node(node, env);//protection
		str = ft_strjoin("PWD=", getcwd(buffer, PATH_MAX));
		node_init(node, str, EXPORTED);
		env_add_back(&env, node);
	}	
	node_home_cpy(env);
	return(env);
}
