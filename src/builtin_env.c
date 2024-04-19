/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:23:08 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/19 18:31:22 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
		if (str[ret] >= '+' && str[ret - 1] == '+') //+ error = 1
		{
			export_error(str);
			return (1);
		}
		ret--;
	}
	return (-1);
}

int	ft_strcmp_export(const char *s1, const char *s2)
{
	while ((*s1 || *s2) && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	builtin_env(char **envp)
{
	// env sans arg return=0
	// env avec arg doit etre chemin acces
	// si existe pas->127,si acces refuse->126
	if (envp == NULL)
		return ;
	while (*envp)
	{
		if (ft_strchr(*envp, '='))
		{
			ft_putstr_fd(*envp, STDOUT_FD);
			write(STDOUT_FD, "\n", 1);
		}
		envp++;
		return ;
	}
}
