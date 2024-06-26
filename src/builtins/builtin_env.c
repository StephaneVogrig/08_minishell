/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:23:08 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/19 16:59:06 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	env(t_env *env)
{
	if (env == NULL)
		return (127);
	env_display(env, EXPORTED);
	return (EXIT_SUCCESS);
}

int	builtin_env(t_cmd *cmd, t_env **envp)
{
	t_list	*argv;
	int		error;

	argv = cmd->argv;
	argv = argv->next;
	if (argv)
	{
		fd_printf(STDERR_FD, "env: invalid option\n");
		return (125);
	}
	error = env(*envp);
	return (error);
}
