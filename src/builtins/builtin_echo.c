/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:20:41 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/18 17:36:24 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "environment.h"

static int	echo_n(t_list *argv)
{
	int	size;

	size = ft_lstsize(argv);
	while (size >= 2)
	{
		ft_printf("%s ", argv->content);
		argv = argv->next;
		size--;
	}
	ft_printf("%s", argv->content);
	return (EXIT_SUCCESS);
}

static int	echo(t_list *argv)
{
	int	size;

	size = ft_lstsize(argv);
	while (size >= 2)
	{
		ft_printf("%s ", argv->content);
		argv = argv->next;
		size--;
	}
	ft_printf("%s\n", argv->content);
	return (EXIT_SUCCESS);
}

t_bool	check_if_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (FALSE);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	builtin_echo(t_cmd *cmd, t_env **env)
{
	t_list	*argv;

	(void)env;
	argv = cmd->argv;
	argv = argv->next;
	if (!argv)
	{
		write(1, "\n", 1);
		return (EXIT_SUCCESS);
	}
	if (!check_if_n(argv->content))
		return (echo(argv));
	argv = argv->next;
	while (argv)
	{
		if (check_if_n(argv->content))
			argv = argv->next;
		else
			return (echo_n(argv));
	}
	return (EXIT_SUCCESS);
}
