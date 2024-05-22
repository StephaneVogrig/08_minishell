/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:20:41 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/22 01:41:12 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_bool	is_num(char *str)
{
	int	i;

	i = 0;
	if ((str[0] == '-' || str[0] == '+') && str[1] != '\0')
	{
		if (!ft_isdigit(str[1]))
			return (FALSE);
		i++;
	}
	while (str[i] == ' ' || str[i] == '\t')//mod
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[1] != '\0')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '\t' && str[i] != ' ')//mod
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	exit_val_2(t_cmd *cmd)
{
	char	*argv;

	if (!cmd->next && !cmd->previous)
		write(STDERR_FD, "exit\n", 5);
	argv = cmd->argv->next->content;
	fd_printf(STDERR_FD, "minishel : exit : %s", argv);
	fd_printf(STDERR_FD, " : numeric argument required\n");
	return (2);
}

t_bool	exit_val_num(char *argv, int *exit_code)
{
	long long	exit_val;

	if (!is_num(argv))
		return (FALSE);
	exit_val = ft_atol(argv);
	if(len_num(exit_val) != len_str_num(argv))
		return (FALSE);
	*exit_code = (int)exit_val;
	return(TRUE);
}

int	exit_too_many(t_cmd *cmd)
{
	(void)cmd;
	if (!cmd->next && !cmd->previous)
		write(STDERR_FD, "exit\n", 5);
	fd_printf(STDERR_FD, "minishell : exit : too many arguments\n");
	return (EXIT_FAILURE);
}

int	builtin_exit(t_cmd *cmd, t_env *env)
{
	int	exit_code;

	exit_code = 0;
	if (!cmd->argv->next)
	{
		if (cmd->next || cmd->previous)
			return(exit_status_get_int(env));
		return (-1);
	}
	if (exit_val_num(cmd->argv->next->content, &exit_code) == FAILURE)
		exit_code = exit_val_2(cmd);
	else if (ft_lstsize(cmd->argv) > 2)
		return(exit_too_many(cmd));
	if (!cmd->next && !cmd->previous)
	{
		exit_status_set(exit_code, env);
		exit_code = -1;
	}
	return (exit_code);
}
