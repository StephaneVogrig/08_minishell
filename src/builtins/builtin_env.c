/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:23:08 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/05 14:22:47 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	env(t_env *env)
{
	if (env == NULL)
		return (127);
	display_the_list(env, EXPORTED);
	return (0);
}

int	builtin_env(t_cmd *cmd, t_env *envp)
{
	t_list	*argv;
	int		error;

	argv = cmd->argv;
	argv = argv->next;

	if (argv)
	{
		fd_printf(STDERR_FD, "minishell: env: args not supported\n");
		return (1);
	}
	error = env(envp);
	if (error == ENOMEM)
	{
		cmd_free(cmd);
		env_free(envp);
		exit(EXIT_FAILURE);
	}
	return (error);
}
