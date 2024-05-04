/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:39:44 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/04 18:29:38 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "environment.h"

t_bool	shlvl_var_init(t_env *node, char *str, int n) // mettre dans utils ?
{
	node->name = ft_strndup(str, n);
	if (!node->name)
		return (FAILURE);
	if (str[n] != '\0')
	{
		node->value = ft_strdup(&str[n + 1]);
		if (!node->value)
			return (FAILURE);
		node->type = EXPORTED;
	}
	else
	{
		node->value = malloc(1);
		if (!node->value)
			return (FAILURE);
		node->value[0] = '\0';
		node->type = NO_VALUE;
	}
	node->next = NULL;
	return (SUCCESS);
}

int	shlvl_export_new_node(t_env *env, char *str, int n) // mettre dans utils ?
{
	t_env *node;

	node = malloc(sizeof(*node));
	if (!node)
		return (ENOMEM);
	if (!shlvl_var_init(node, str, n))
		return (ENOMEM);
	lst_add_back(&env, node);
	return (0);
}

void	init_shlvl(t_env *env)
{
	t_env *node;
	char *value;
	int num;
	char *new;

	node = env_get_node_n(env, "SHLVL", 5);
	value = node->value;
	if (!value) // ON CREE SHLVL = 1
	{
		shlvl_export_new_node(env, "SHLVL=1", 6);
		return ;
		// add_node_shlvl();
	}
	printf("atoi\n");
	num = ft_atoi(value) + 1;
	printf("itoa\n");
	new = ft_itoa(num);
	free(value);
	value = ft_strdup(new);
	if (!value)
		return ;
}