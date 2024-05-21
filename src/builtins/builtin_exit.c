/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:20:41 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/21 15:33:51 by smortemo         ###   ########.fr       */
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

int	exit_val_2(t_cmd *cmd, t_env *env, char *argv)
{
	fd_printf(STDERR_FD, "minishel : exit : %s", argv);
	fd_printf(STDERR_FD, " : numeric argument required\n");
	cmd_free(cmd);
	env_free(env);
	exit(2);
}

int	exit_val_num(t_cmd *cmd, t_env *env, char *argv)
{
	long long	exit_val;

	exit_val = ft_atol(argv);
	if(exit_val < 0 && !ft_strchr(argv, '-'))
		exit_val_2(cmd, env, argv);
	if(exit_val > 0 && ft_strchr(argv, '-'))
		exit_val_2(cmd, env, argv);
	cmd_free(cmd);
	env_free(env);
	exit((int)exit_val);
}

int	builtin_exit(t_cmd *cmd, t_env *env)
{
	if (!cmd->argv->next)
	{
		if (cmd->next || cmd->previous)
			exit(exit_status_get_int(env));
		write(1, "exit\n", 5);
		return (-1);
	}
	if (!is_num(cmd->argv->next->content))
		exit_val_2(cmd, env, cmd->argv->next->content);
	if (ft_lstsize(cmd->argv) > 2)
	{
		fd_printf(STDERR_FD, "minishell : exit : too many arguments\n");
		return (EXIT_FAILURE);
	}
	exit_val_num(cmd, env, cmd->argv->next->content);
	return (0);
}
