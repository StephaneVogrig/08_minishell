/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_alone.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:22:07 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/27 13:46:19 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	env_sorted_display(t_env *env)
{
	while (env != NULL)
	{
		if (env->type == EXPORTED)
		{
			if (env->name[0] == '_' && env->name[1] == '\0')
				env = env->next;
			else
			{
				printf("declare -x %s=\"%s\"\n", env->name, env->value);
				env = env->next;
			}
		}
		else
		{
			printf("declare -x %s\n", env->name);
			env = env->next;
		}
	}
}

static t_bool	tab_to_lst(char **sorted_tab)
{
	t_env	*sorted_env;

	sorted_env = NULL;
	if (envp_to_env(sorted_tab, &sorted_env) == FAILURE)
		return (FAILURE);
	env_sorted_display(sorted_env);
	env_free(sorted_env);
	return (SUCCESS);
}

static t_bool	strtab_sort(char **to_sort)
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
		return (tab_to_lst(to_sort));
	else
		strtab_sort(to_sort);
	return (SUCCESS);
}

static t_bool	fill_tab_to_sort(t_env *env, char **tab_to_sort)
{
	int		i;

	i = 0;
	while (env)
	{
		if ((env->type == EXPORTED || env->type == NO_VALUE))
		{
			if (env->type == EXPORTED && env->value[0] != '\0')
				tab_to_sort[i] = env_join(env->name, env->value);
			else if (env->type == EXPORTED && env->value[0] == '\0')
				tab_to_sort[i] = ft_strjoin(env->name, "=");
			else if (env->type == NO_VALUE)
				tab_to_sort[i] = ft_strdup(env->name);
			if (!tab_to_sort[i])
			{
				perror("minishell: fill_tab_to_sort");
				strtab_free(tab_to_sort);
				return (FAILURE);
			}
			i++;
		}
		env = env->next;
	}
	return (SUCCESS);
}

t_bool	display_envp_sorted(t_env *env)
{
	char	**tab_to_sort;

	tab_to_sort = ft_calloc(env_size(env, ALL) + 1, sizeof(*env));
	if (!tab_to_sort)
		return (ENOMEM);
	if (fill_tab_to_sort(env, tab_to_sort) == FAILURE)
		return (FAILURE);
	if (strtab_sort(tab_to_sort) == ENOMEM)
	{
		perror("minishell: export");
		strtab_free(tab_to_sort);
		return (FAILURE);
	}
	strtab_free(tab_to_sort);
	return (SUCCESS);
}
