/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_alone.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:22:07 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/19 15:32:42 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	env_sorted_display(t_env *env)
{
	while (env != NULL)
	{
		if(env->type == EXPORTED)
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		else
			printf("declare -x %s\n", env->name);
		env = env->next;
	}
}

t_bool	node_init_v2(t_env *node, char *str)///possible de modifier node_init ?
{
	int	index;

	if (ft_strchr(str, '='))
	{
		index = ft_strchr_i(str, '=');
		node->value = ft_strdup(&str[index + 1]);
		if (!node->value)
			return (FAILURE);
		node->type = EXPORTED;
	}
	else
	{
		index = ft_strlen(str);
		node->value = malloc(1);
		if (!node->value)
			return (FAILURE);
		node->type = INTERNAL;
	}
	node->name = ft_strndup(str, index);
	if (!node->name)
		return (FAILURE);
	node->next = NULL;
	return (SUCCESS);
}

t_env	*envp_to_env_v2(char **envp)///possible de modifier envp_to_env ?
{
	t_env	*env;
	t_env	*node;

	if (!envp)
		return (NULL);
	node = NULL;
	env = NULL;
	while (*envp)
	{
		node = malloc(sizeof(*node));
		if (!node)
		{
			env_free(env);
			return (NULL);
		}
		if (node_init_v2(node, *envp) == FAILURE)
		{
			env_free(env);
			return (NULL);
		}
		env_add_back(&env, node);
		envp++;
	}
	return (env);
}

int	modify_tab(char **sorted_tab)
{
	t_env	*sorted_env;
	t_env	*node;
	
	node = NULL;
	sorted_env = NULL;
	sorted_env = envp_to_env_v2(sorted_tab);
	if (!sorted_env)
		return (ENOMEM);
	env_sorted_display(sorted_env);
	env_free(sorted_env);
	return (0);
}

void	strtab_sort(char **to_sort)
{
	int		i;
	char	*temp;
	int		count;

	count = 0;
	temp = NULL;
	i = 1;
	while (to_sort[i])
	{
		if (ft_strcmp(to_sort[i - 1], to_sort[i]) > 0)
		{
			temp = to_sort[i];
			to_sort[i] = to_sort[i - 1];
			to_sort[i - 1] = temp;
			count++;
		}
		i++;
	}
	if (count == 0)
		modify_tab(to_sort);
	else
		strtab_sort(to_sort);
}

char	**env_to_envp_export(t_env *env, int size)
{
	char	**envp;
	int		i;

	i = 0;
	envp = calloc(size + 2, sizeof(*envp));
	if (!envp)
		return (NULL);
	while (i <= size)
	{
		if (env->name[0] == '_' && env->name[1] == '\0')
			env = env->next;
		else
		{
			if (env->type == EXPORTED && env->value[0] != '\0')
				envp[i] = env_join(env->name, env->value);
			else if (env->type == NO_VALUE && env->value[0] == '\0')
				envp[i] = ft_strdup(env->name);
			else
				envp[i] = ft_strjoin(env->name, "=");
			if (!envp[i])
			{
				strtab_free(envp);
				return (NULL);
			}
			i++;
			env = env->next;
		}
	}
	return (envp);
}

int	display_envp_sorted(t_env *envp)
{
	char **tab_to_sort;

	tab_to_sort = env_to_envp_export(envp, env_size(envp, ALL));
	strtab_sort(tab_to_sort);
	strtab_free(tab_to_sort);
	return (0);
}