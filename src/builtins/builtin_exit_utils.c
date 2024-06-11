/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:26:21 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 19:18:01 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_exit_utils.h"

t_bool	is_in_pipe(t_cmd *cmd)
{
	if (cmd->next || cmd->previous)
		return (TRUE);
	return (FALSE);
}

void	print_exit(t_cmd *cmd, t_env *env)
{
	if (!is_in_pipe(cmd) && shell_mode_is_interactive(env))
		write(STDERR_FD, "exit\n", 5);
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
