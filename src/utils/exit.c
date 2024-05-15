/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:56:00 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/15 19:38:48 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

void	minishell_free(t_cmd *cmd, char *str, char **argv, t_env *env)
{
	if (str)
		free(str);
	if (argv)
		strtab_free(argv);
	if (env)
		env_free(env);
	if (cmd)
		pipeline_free(&cmd);
}

void	exit_on_file_error(const char *msg, t_char_m **argv, t_env *env)
{
	fd_printf(STDERR_FD, "%s: %s\n", *argv, msg);
	minishell_free(NULL, NULL, argv, env);
	exit(127);
}

void	exit_on_open_error(char *file_path, int fd)
{
	fd_printf(STDERR_FD, "minishell: %s: %s\n", file_path, strerror(errno));
	close(fd);
	exit(EXIT_FAILURE);
}

void	exit_on_failure(t_cmd *cmd, char *str, char **argv, t_env_m *env)
{
	minishell_free(cmd, str, argv, env);
	exit(EXIT_FAILURE);
}
