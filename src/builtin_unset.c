/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:23 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/29 22:48:06 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// ajouter dans libft ?
// int	ft_strtab_size(char **strtab)
// {
// 	int	i;

// 	if (!strtab)
// 		return (0);
// 	i = 0;
// 	while (*strtab++)
// 		i++;
// 	return (i);
// }

// char	**builtin_unset(char **envp, char *str)
// {
// 	int		i;
// 	int		j;
// 	int		len;
// 	char	**tab_temp;

// 	if (!env_get(envp, str))
// 		return (envp);
// 	j = 0;
// 	i = 0;
// 	len = ft_strlen(str);
// 	tab_temp = mem_calloc(ft_strtab_size(envp), sizeof(char **));
// 	while (envp[j])
// 	{
// 		if (ft_strncmp(envp[j], str, len) != 0)
// 			tab_temp[i++] = ft_strdup(envp[j]);
// 		if (ft_strncmp(envp[j], str, len) == 0 && envp[j][len] != '=')
// 			tab_temp[i++] = ft_strdup(envp[j]);
// 		j++;
// 	}
// 	strtab_free(envp);
// 	envp = tab_temp;
// 	return (envp);
// }

int	builtin_unset(t_env *env, char *str)
{
	t_env *temp;

	if (!env || !str)
		return (0);
	while (env)
	{
		if (ft_strcmp(env->name, str))
		{
			free(env->name);
			free(env->value);
			temp = env;
			while (temp)
			{
				temp = env->next;
				env = temp;
			}
			free(temp);
			env->next = NULL;
			return (0);
		}
		env = env->next;
	}
	return (0);
}