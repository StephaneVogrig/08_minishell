/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:23 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/28 15:37:31 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// ajouter dans libft ?
int	ft_strtab_size(char **strtab)
{
	int	i;

	if (!strtab)
		return (0);
	i = 0;
	while (*strtab++)
		i++;
	return (i);
}

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
// 	return (tab_temp);
// }

int	builtin_unset(char **envp, char *str)
{
	int		i;
	int		len;
	char	**tab_str;

	if (!str)
	{
		printf("unset: not enough arguments\n");
		return (1);
	}
	tab_str = ft_split(str, ' ');
	if (!env_get(envp, tab_str[0]))
	{
		strtab_free(tab_str);
		return (0);
	}
	i = 0;
	len = ft_strlen(tab_str[0]);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], tab_str[0], len) == 0 && envp[i][len] == '=')
		{
			while (envp[i + 1])
			{
				free(envp[i]);
				envp[i] = ft_strdup(envp[i + 1]);
				i++;
			}
			free(envp[i]);
			envp[i] = NULL;
			strtab_free(tab_str);
			return (0);
		}
		i++;
	}
	return (0);
}
