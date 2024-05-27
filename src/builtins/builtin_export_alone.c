/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_alone.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:22:07 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/27 01:53:46 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	env_sorted_display(t_env *env)
{
	while (env != NULL)
	{
		if(env->type == EXPORTED)
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

int	tab_to_lst(char **sorted_tab)
{
	t_env	*sorted_env;
	
	sorted_env = envp_to_env(sorted_tab);
	if (!sorted_env)
		return (ENOMEM);
	env_sorted_display(sorted_env);
	env_free(sorted_env);
	return (0);
}

int	strtab_sort(char **to_sort)
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
	return (0);
}

char	**env_to_envp_export(t_env *env, char **envp)
{
	int		i;

	i = 0;
	while(env)
	{
		if ((env->type == EXPORTED || env->type == NO_VALUE))
		{
			if (env->type == EXPORTED && env->value[0] != '\0')
				envp[i] = env_join(env->name, env->value);
			else if (env->type == EXPORTED && env->value[0] == '\0')
				envp[i] = ft_strjoin(env->name, "=");
			else if (env->type == NO_VALUE)
				envp[i] = ft_strdup(env->name);
			if (!envp[i])
			{
				strtab_free(envp);
				return (NULL);
			}
			i++;
		}
		env = env->next;
	}
	return (envp);
}

int	display_envp_sorted(t_env *envp)
{
	char **tab_to_sort;

	tab_to_sort = ft_calloc(env_size(envp, ALL) + 1, sizeof(*envp));
	if (!tab_to_sort)
		return (ENOMEM);
	tab_to_sort = env_to_envp_export(envp, tab_to_sort);
	if(strtab_sort(tab_to_sort) == ENOMEM)
	{
		perror("minishell: export");
		strtab_free(tab_to_sort);
		return (ENOMEM);
	}
	strtab_free(tab_to_sort);
	return (0);
}