/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:22:47 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/13 03:44:01 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"

void	exit_after_execve(int error, char *path, char **argv)
{
	struct stat	buf;

	if (error == EACCES)
	{
		if (stat(*argv, &buf) == 0 && (S_ISDIR(buf.st_mode)))
			fd_printf(STDERR_FILENO, "minishell: %s: Is a directory\n", *argv);
		else
			fd_printf(STDERR_FILENO, \
						"minishell: %s: Permission denied\n", *argv);
		error = 126;
	}
	else if (error == ENOENT)
	{
		fd_printf(STDERR_FILENO, \
						"minishell: %s: No such file or directory\n", path);
		error = 127;
	}
	minishell_free(NULL, path, argv, NULL);
	exit(error);
}

void	exec_cmd(t_cmd_m *cmd, t_env_m **env, t_cmd *data)
{
	char	*path;
	char	**argv;
	char	**envp;

	if (!cmd->argv)
	{
		minishell_free(cmd, NULL, NULL, *env);
		exit(EXIT_SUCCESS);
	}
	path = cmd_path(cmd, *env);
	if (!path)
		exit_on_file_error("command not found", cmd, *env, data);
	argv = argvlist_to_argvtab(&cmd->argv);
	minishell_free(data, NULL, NULL, NULL);
	if (!argv)
		exit_on_failure(NULL, path, NULL, *env);
	envp = env_to_envp(*env);
	env_free(*env);
	if (!envp)
		exit_on_failure(NULL, path, argv, *env);
	signal(SIGINT, SIG_DFL);
	execve(path, argv, envp);
	strtab_free(envp);
	exit_after_execve(errno, path, argv);
}
