/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:59:17 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/18 19:47:46 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

char	*create_home_path(t_env *env)
{
	char	*str;
	int		index;
	char	*home;
	char buffer[PATH_MAX];

	(void)env;
	str = getcwd(buffer, PATH_MAX);
	if (!str)
		return(NULL);
	index = ft_strstr(str, "/nfs/homes/");
	while (str[index] != '/')
		index++;
	home = ft_strndup(str, index + 1);
	return (home);
}

void	node_home_cpy(t_env *env)
{
	t_env	*node;
	char	*str;

	node = malloc(sizeof(*node));
	if (!node)
		return ;
	node->name = ft_strdup("HOME_cpy");
	if (!node->name)
		return ;
	str = env_get_type(env, "HOME", EXPORTED);
	if (str)
		node->value = ft_strdup(str);
	else
	node->value = create_home_path(env);
	node->type = INTERNAL;
	node->next = NULL;
	env_add_back(&env, node);
	return ;
}