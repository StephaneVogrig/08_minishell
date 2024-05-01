/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:23:08 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/02 00:40:59 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	env(t_env *env)
{
	// env sans arg return=0
	// env avec arg doit etre chemin acces
	// si existe pas->127,si acces refuse->126
	if (env == NULL)
		return (127);
	display_the_list(env, EXPORTED);
	return (0);
}

int	builtin_env(t_cmd *cmd, t_env *envp)
{
	t_list	*argv;
	int		error;
	int		ret;

	ret = 0;
	// printf("builtin ENV -> \n");
	argv = cmd->argv;
	argv = argv->next;
	error = env(envp);
	if (error == ENOMEM)
	{
		cmd_free(cmd);
		env_free(envp);
		exit(EXIT_FAILURE);
	}
	return (error);
}
