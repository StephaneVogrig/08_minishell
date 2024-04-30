/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_alone.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:22:07 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/30 23:49:24 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// void	display_tab_export(char **tab, int i)
// {
// 	while (tab[i])
// 	{
// 		if (tab[i][0] == '_' && tab[i][1] == '=')
// 			break ;
// 		printf("declare -x %s", tab[i]);
// 		free(tab[i]);
// 		i++;
// 		if (tab[i] != NULL)
// 			printf("\"%s\"", tab[i]);
// 		free(tab[i]);
// 		printf("\n");
// 		i++;
// 	}
// 	if(tab[i] == NULL)
// 	{
// 		//strtab_free(tab);

// 		free(tab);
// 		return ;
// 	}
// 	// else
// 	// {
// 	// 	free(tab[i]);
// 	// 	free(tab[i++]);
// 	// }
// 	display_tab_export(tab, i + 2);
// }

void	display_tab_export(char **tab, int i)
{
	while (tab[i])
	{
		printf("declare -x %s", tab[i]);
		free(tab[i]);
		i++;
		if (tab[i] != NULL)
			printf("\"%s\"", tab[i]);
		free(tab[i]);
		printf("\n");
		i++;
	}
	free(tab);
	return ;
}

void	modify_tab(char **sorted_tab)
{
	char	**tab_to_display;
	int		i;
	int		j;
	int		count;
	int		len;

	len = 2 * ft_strtab_size(sorted_tab);
	tab_to_display = (char **)malloc(sizeof(char *) * ((len) + 1));
	j = 0;
	i = 0;
	while (sorted_tab[j])
	{
		count = ft_strchr_i(sorted_tab[j], '=');
		if (count != 0)
		{
			tab_to_display[i] = ft_strndup(sorted_tab[j], count + 1);
			i++;
			tab_to_display[i] = ft_strdup(&sorted_tab[j][count + 1]);
		}
		else
		{
			tab_to_display[i] = ft_strdup(sorted_tab[j]);
			i++;
			tab_to_display[i] = NULL;
		}
		i++;
		j++;
	}
	tab_to_display[i] = NULL;
	display_tab_export(tab_to_display, 0);
}

void	export_alone(char **to_sort)
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
		export_alone(to_sort);
}

int	env_size_envp_all(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_to_envp_export(t_env *env)
{
	char	**envp;
	char	**temp;
	int		i;
	int		size;

	i = 0;
	size = env_size_envp_all(env);
	envp = calloc(size + 1, sizeof(*envp));
	if (!envp)
		return (NULL);
	while (i < size - 1)
	{
		if (env->name[0] == '_' && env->name[1] == '\0')
			env = env->next;
		else
		{
			if (env->value[0] != '\0')
				envp[i] = env_join(env->name, env->value);
			else
				envp[i] = ft_strdup(env->name);
			if (!envp[i])
			{
				strtab_free(envp);
				return (NULL);
			}
			i++;
			env = env->next;
		}
	}
	// printf("*****************\n");
	// strtab_print(envp);
	// printf("*****************\n");
	return (envp);
}

int	display_envp_sorted(t_env *envp)
{
	char **tab_to_sort;

	tab_to_sort = env_to_envp_export(envp);
	export_alone(tab_to_sort);
	strtab_free(tab_to_sort);
	return (0);
}