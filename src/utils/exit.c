/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:56:00 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/13 03:54:20 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

void	exit_on_file_error(char *msg, t_cmd *cmd, t_env *env, t_cmd *data)
{
	fd_printf(STDERR_FD, "%s: %s\n", cmd->argv->content, msg);
	minishell_free(data, NULL, NULL, env);
	exit(127);
}

void	exit_on_open_error(char *file_path, int fd)
{
	fd_printf(STDERR_FD, "minishell: %s: %s\n", file_path, strerror(errno));
	close(fd);
	exit(EXIT_FAILURE);
}

void	exit_on_failure(t_cmd *cmd, char *str, char **argv, t_env *env)
{
	minishell_free(cmd, str, argv, env);
	exit(EXIT_FAILURE);
}
