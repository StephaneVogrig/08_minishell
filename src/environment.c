/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:59:17 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/10 23:44:42 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

int	strtab_size(char **strtab)
{
	int	i;

	if (!strtab)
		return (0);
	i = 0;
	while (*strtab++)
		i++;
	return (i);
}

char	**env_dup(char **envp)
{
	char	**new;
	char	**current;
	int		size;

	if (!envp)
		return (NULL);
	size = strtab_size(envp) + 1;
	new = ft_calloc(sizeof(char *), (size));
	if (!new)
		return (NULL);
	current = new;
	while (*envp)
	{
		*current = ft_strdup(*envp++);
		if (!*current)
		{
			strtab_free(new);
			return (NULL);
		}
		current++;
	}
	return (new);
}

char	*env_get(char **env, char *str)
{
	int	size;
	int	ok;

	if (!env || !str)
		return (NULL);
	size = ft_strlen(str);
	while (*env)
	{
		if (!ft_strncmp(*env, str, size))
			if (*(*env + size) == '=')
				return (*env + size + 1);
		env++;
	}
	return (NULL);
}
