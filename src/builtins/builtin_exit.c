/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:20:41 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/23 18:03:48 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exit_numeric_required(t_cmd *cmd, t_env *env)
{
	char	*argv;

	print_exit(cmd, env);
	argv = cmd->argv->next->content;
	fd_printf(STDERR_FD, "minishel : exit : %s", argv);
	fd_printf(STDERR_FD, " : numeric argument required\n");
	if (is_in_pipe(cmd))
		return (2);
	exit_status_set(2, env);
	return (-1);
}

int	exit_too_many(t_cmd *cmd, t_env *env)
{
	print_exit(cmd, env);
	fd_printf(STDERR_FD, "minishell : exit : too many arguments\n");
	return (EXIT_FAILURE);
}

int	exit_no_arg(t_cmd *cmd, t_env *env)
{
	if (is_in_pipe(cmd))
		return (exit_status_get_int(env));
	print_exit(cmd, env);
	return (-1);
}

int	builtin_exit(t_cmd *cmd, t_env *env)
{
	int		exit_code;

	exit_code = 0;
	if (!cmd->argv->next)
		return (exit_no_arg(cmd, env));
	if (convert_arg(cmd->argv->next, &exit_code) == FAILURE)
		return (exit_numeric_required(cmd, env));
	if (cmd->argv->next->next)
		return (exit_too_many(cmd, env));
	if (!is_in_pipe(cmd))
	{
		print_exit(cmd, env);
		exit_status_set(exit_code, env);
		exit_code = -1;
	}
	return (exit_code);
}
