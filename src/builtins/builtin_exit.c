/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:20:41 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/20 05:54:28 by svogrig          ###   ########.fr       */
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
	// while (str[i] == ' ')
	// 	i++;
	// if ((str[i] == '-' || str[i] == '+') && str[1] != '\0')
	// 	i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	exit_val_2(t_cmd *cmd, t_env *env, char *argv)
{
	write(1, "exit\n", 5);
	fd_printf(STDERR_FD, "minishel : exit : %s", argv);
	fd_printf(STDERR_FD, " : numeric argument required\n");
	cmd_free(cmd);
	env_free(env);
	exit(2);
}

int	exit_val_num(t_cmd *cmd, t_env *env, char *argv)
{
	long long	error;

	error = ft_atol(argv);
	if(error < 0 && !ft_strchr(argv, '-'))
		exit_val_2(cmd, env, argv);
	if(error > 0 && ft_strchr(argv, '-'))
		exit_val_2(cmd, env, argv);
	cmd_free(cmd);
	env_free(env);
	write(1, "exit\n", 5);
	exit((int)error);
}

int	exit_mini(t_cmd *cmd, t_env *env, t_list *argv)
{
	if (!argv->next)
	{
		if (!is_num(argv->content))
			exit_val_2(cmd, env, argv->content);
		exit_val_num(cmd, env, argv->content);
	}
	if (argv->next)
	{
		if (!is_num(argv->content))
			exit_val_2(cmd, env, argv->content);
		else
		{
			if(ft_atol(argv->content) < 0 && !ft_strchr(argv->content, '-'))
				exit_val_2(cmd, env, argv->content);
			if(ft_atol(argv->content) > 0 && ft_strchr(argv->content, '-'))
				exit_val_2(cmd, env, argv->content);
			write(1, "exit\n", 5);
			fd_printf(STDERR_FD, "minishell : exit : too many arguments\n");
		}
	}
	return (1);
}

int	builtin_exit(t_cmd *cmd, t_env *env)
{
	t_list *argv;
	int		exit_code;

	argv = cmd->argv;
	argv = argv->next;
	if (!argv)
	{
		exit_code = exit_status_get_int(env);
		cmd_free(cmd);
		env_free(env);
		write(1, "exit\n", 5);
		exit(exit_code);
	}
	return (exit_mini(cmd, env, argv));
}