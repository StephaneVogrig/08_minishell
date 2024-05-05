/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:56:00 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/04 22:30:51 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

void	exit_on_is_directory(char *path, char *to_free, char **argv)
{
	fd_printf(STDERR_FD, "minishell: %s: is a directory\n", *path);
	strtab_free(argv);
	if (to_free)
		free(to_free);
	exit(126);
}

void	exit_on_acces_denied(char *path, char *to_free, char **argv)
{
	fd_printf(STDERR_FD, "minishell: %s: %s\n", *path, strerror(errno));
	strtab_free(argv);
	if (to_free)
		free(to_free);
	exit(127);
}

void	exit_on_cmd_not_found(char **argv, t_env *env)
{
	env_free(env);
	fd_printf(STDERR_FD, "%s: command not found\n", *argv);
	strtab_free(argv);
	exit(127);
}

void	exit_on_open_error(char *file_path, int fd)
{
	fd_printf(STDERR_FD, "minishell: %s: %s\n", file_path, strerror(errno));
	close(fd);
	exit(EXIT_FAILURE);
}

void	exit_on_failure(t_char_m *str, t_char_m **argv, t_env_m *env)
{
	if (str)
		free(str);
	if (argv)
		strtab_free(argv);
	if (env)
		env_free(env);
	exit(EXIT_FAILURE);
}

