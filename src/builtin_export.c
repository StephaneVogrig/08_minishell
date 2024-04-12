/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:13:40 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/12 21:44:56 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// possible d'ajouter a libft du projet?
int	ft_strchr_i(char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (0);
}

// recup de ma libft: possible d'ajouter a libft du projet ?
char	*ft_strjoin_free_s1(char const *s1, char const *s2)
{
	unsigned int	i;
	char			*tab;
	int				k;

	tab = NULL;
	if (s1 == 0 || s2 == 0)
		return (malloc(0));
	tab = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!tab)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
		tab[k++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		tab[k++] = s2[i++];
	tab[k] = '\0';
	free((char *)s1);
	return (tab);
}

void	export_error(char *str)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("' : not a valid identifier\n", 2);
}

int	export_check_str(char **envp, char *str)
{
	int		ret;
	char	*lst;

	lst = "!#$%%?$*-.,/}{}[]@~:";
	ret = ft_strchr_i(str, '=');
	if (!ret) //+ error = 0
		return (0);
	while (ret >= 0)
	{
		if (ft_strchr(lst, str[ret])) //+ error = 1
		{
			export_error(str);
			return (1);
		}
		if (str[ret] >= '+' && str[ret - 1] == '+') //+ error = 1
		{
			export_error(str);
			return (1);
		}
		ret--;
	}
	return (-1);
}

int	export_check_exist(char **envp, char *str)
{
	int	i;
	int	index;

	i = 0;
	index = ft_strchr_i(str, '=');
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, index) == 0 && envp[i][index] == '=')
		{
			free(envp[i]);
			envp[i] = ft_strdup(str);
			return (1);
		}
		if (ft_strncmp(envp[i], str, index - 1) == 0 && str[index - 1] == '+')
		{
			envp[i] = ft_strjoin_free_s1(envp[i], &(*str) + 4 + 2);
			return (1);
		}
		i++;
	}
	return (0);
}
char	**export_alone(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		// is_smallest(envp, i);
		i++;
	}
	return (envp);
}

char	**builtin_export(char **envp, char *str)
{
	int		i;
	char	**tab_temp;
	int		flag;

	if (!envp)
		return (NULL);
	if (!str)
		return (export_alone(envp)); //+code erreur = 0
	if (str[0] == '\0')
	{
		export_error(str);
		return (envp); //+code erreur = 1
	}
	if (export_check_str(envp, str) >= 0)
		return (envp);
	flag = export_check_exist(envp, str);
	tab_temp = mem_calloc(ft_strtab_size(envp) + 2 - flag, sizeof(char **));
	i = -1;
	while (envp[++i])
		tab_temp[i] = envp[i];
	if (flag == 0)
		tab_temp[i] = ft_strdup(str);
	free(envp);
	return (tab_temp); //+code erreur = 0
}
