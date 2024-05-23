/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:20:41 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/23 16:44:58 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_bool	cmd_is_in_pipe(t_cmd *cmd)
{
	if (cmd->next || cmd->previous)
		return (TRUE);
	return (FALSE);
}

void	exit_print_exit(t_cmd *cmd, t_env *env)
{
	(void)env;
	char *value = env_get(env, "-");
	// fd_printf(STDERR_FD, "value = %s\n", value);
	// (void)value;
	if (!cmd_is_in_pipe(cmd) && ft_strchr(value, 'i'))
		write(STDERR_FD, "exit\n", 5);
}

int	exit_numeric_required(t_cmd *cmd, t_env *env)
{
	char	*argv;

	exit_print_exit(cmd, env);
	argv = cmd->argv->next->content;
	fd_printf(STDERR_FD, "minishel : exit : %s", argv);
	fd_printf(STDERR_FD, " : numeric argument required\n");
	if (cmd_is_in_pipe(cmd))
		return (2);
	exit_status_set(2, env);
	return (-1);
}

int	exit_too_many(t_cmd *cmd, t_env *env)
{
	(void)cmd;
	(void)env;
	exit_print_exit(cmd, env);
	fd_printf(STDERR_FD, "minishell : exit : too many arguments\n");
	return (EXIT_FAILURE);
}

int exit_no_arg(t_cmd *cmd, t_env *env)
{
	if (cmd_is_in_pipe(cmd))
		return(exit_status_get_int(env));
	exit_print_exit(cmd, env);
	return (-1);
}

t_bool	convert_arg(t_list *argv, int *exit_code)
{
	char	*endptr;

	*exit_code = (int)mini_strtol(argv->content, &endptr);
	while (is_blank(*endptr))
		endptr++;
	if (endptr == argv->content || *endptr != '\0')
		return (FAILURE);
	return (SUCCESS);
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
		return(exit_too_many(cmd, env));
	if (!cmd_is_in_pipe(cmd))
	{
		exit_print_exit(cmd, env);
		exit_status_set(exit_code, env);
		exit_code = -1;
	}
	return (exit_code);
}
