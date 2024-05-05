/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:20:41 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/05 14:38:01 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "debug.h" // a enlever
#include "environment.h"

t_bool	is_num(char *str)
{
	int	i;

	i = 0;
	if ((str[0] == '-' || str[0] == '+') && str[1] != '\0')
		i++;
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
	ft_printf("exit\n");
	fd_printf(STDERR_FD, "minishel : exit : %s", argv);
	fd_printf(STDERR_FD, " : numeric argument required\n");
	cmd_free(cmd);
	env_free(env);
	exit(2);
}

int	exit_val_num(t_cmd *cmd, t_env *env, char *argv)
{
	int	error;

	error = ft_atoi(argv);
	cmd_free(cmd);
	env_free(env);
	ft_printf("exit\n");
	exit(error);
}

int	exit_mini(t_cmd *cmd, t_env *env, t_list *argv)
{
	if (!argv)
	{
		cmd_free(cmd);
		env_free(env);
		ft_printf("exit\n");
		exit(0);
	}
	else if (!argv->next)
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
			ft_printf("exit\n");
			fd_printf(STDERR_FD, "minishell : exit : too many arguments\n");
		}
	}
	return (1);
}
int	builtin_exit(t_cmd *cmd, t_env *env)
{
	t_list *argv;
	// t_cmd *lst;

	argv = cmd->argv;
	argv = argv->next;
	// lst = cmd;
	// lst = lst->next;
	// if (lst)
	// 	printf("EXIT ON START OR MIDDLE OF PIPE\n");
	// else
	return (exit_mini(cmd, env, argv));
}