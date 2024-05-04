/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:59:17 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/05 00:16:54 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

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

t_bool	node_init(t_env *node, char *str, int type)
{
	int	index;

	index = ft_strchr_i(str, '=');
	node->name = ft_strndup(str, index);
	if (!node->name)
		return (FAILURE);
	node->value = ft_strdup(&str[index + 1]);
	if (!node->value)
		return (FAILURE);
	node->type = type;
	node->next = NULL;
	return (SUCCESS);
}

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
		node->value = ft_strdup_free(create_HOME_path(env));
	if (!node->value)
	{
		node->value = ft_calloc( sizeof(char*), 0);
		return ;
	}
	node->type = INTERNAL;
	node->next = NULL;
	lst_add_back(&env, node);
	return ;
}
