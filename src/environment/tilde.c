/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:59:17 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/19 19:22:07 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

char	*create_home_path(t_env *env)
{
	char	*str;
	int		index;
	char	*home;
	char	buffer[PATH_MAX];

	(void)env;
	str = getcwd(buffer, PATH_MAX);
	if (!str)
		return (NULL);
	index = ft_strstr(str, "/nfs/homes/");
	while (str[index] != '/')
		index++;
	home = ft_strndup(str, index + 1);
	if (!home)
	{
		free(str);
		return (NULL);
	}
	return (home);
}

int	node_home_cpy(t_env *env)
{
	t_env	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (ENOMEM);
	node->name = ft_strdup("HOME_cpy");
	if (!node->name)
		return (ENOMEM);
	node->value = create_home_path(env);
	if (!node->value)
		return (ENOMEM);
	node->type = INTERNAL;
	node->next = NULL;
	env_add_back(&env, node);
	return (SUCCESS);
}
