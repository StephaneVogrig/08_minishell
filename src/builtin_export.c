/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:13:40 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/28 21:02:06 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
		return (-1);
	while (ret >= 0)
	{
		if (ft_strchr(lst, str[ret])) //+ error = 1
		{
			export_error(str);
			return (1);
		}
		if (str[ret] == '+' && str[ret - 1] == '+') //+ error = 1
		{
			export_error(str);
			return (1);
		}
		ret--;
	}
	return (-1);
}

int	export_modify_var(char *envp, char *str)
{
	free(envp);
	envp = ft_strdup(str);
	return (1);
}

int	export_check_exist(char **envp, char *str)
{
	int	i;
	int	index;
	int	len;

	i = 0;
	index = ft_strchr_i(str, '=');
	len = ft_strlen(envp[i]);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, index) == 0 && envp[i][index] == '=')
			// ex:  TEST=aaa
			return (export_modify_var(envp[i], str));
		else if (ft_strncmp(envp[i], str, index - 1) == 0 && str[index
				- 1] == '+') // ex: TEST+=newvalue
		{
			envp[i] = ft_strjoin_free_s1(envp[i], &(*str) + index + 1);
			return (1);
		}
		else if (ft_strncmp(envp[i], str, len) == 0 && str[len] == '=')
			// ex : TEST=value (avec TEST qui existe deja)
			return (export_modify_var(envp[i], str));
		i++;
	}
	return (0);
}

char	**builtin_export(char **envp, char *str)
{
	int		i;
	char	**tab_temp;
	int		flag;

	if (!envp)
		return (NULL);
	if (!str)
	{
		tab_temp = env_dup(envp);
		export_alone(tab_temp); //+code erreur = 0
		strtab_free(tab_temp);
		return (envp);
	}
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
/////////////////
int	display_envp(char **envp)
{
	char	**temp;

	temp = env_dup(envp);
	export_alone(temp);
	strtab_free(temp);
	return (0);
}

t_bool	is_valid_arg(char *str)
{
	if (!ft_islaplpha(str[0]))
		return (0);
}

int	builtin_export_(char ***envp, char *str)
{
	if (!envp)
		return (0);
	if (!str)
		return (display_envp(*envp));
	if (!is_valid_arg(str))
		return (1);
	return (export_run(envp, str));
}