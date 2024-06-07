/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:56:00 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/07 18:54:02 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_bonus.h"

void	exit_on_file_error_bonus(const char *msg, t_cmd *cmd, t_env *env, t_cmd *tofree)
{
	fd_printf(STDERR_FD, "%s: %s\n", cmd->argv->content, msg);
	pipelist_free(tofree);
	env_free(env);
	exit(127);
}

void	exit_on_failure_bonus(t_cmd *pipelist, t_env *env)
{
	pipelist_free(pipelist);
	env_free(env);
	exit(EXIT_FAILURE);
}

