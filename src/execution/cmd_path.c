/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:36:25 by stephane          #+#    #+#             */
/*   Updated: 2024/05/21 02:53:22 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_path.h"

char	*path_find_loop(char *paths, t_char_m *buff, t_cmd_m *cmd, t_env_m *env)
{
	char	*temp;
	char	*path;

	path = cmd->argv->content;
	while (*paths)
	{
		temp = buff;
		while (*paths && *paths != ':')
			*temp++ = *paths++;
		*temp++ = '/';
		temp = strcpy_offset(temp, path);
		if (access(buff, F_OK) == 0)
		{
			path = ft_strdup(buff);
			if (!path)
			{
				perror("minishell: path_find_loop: ft_strdup");
				exit_on_failure(cmd, buff, NULL, env);
			}
			return (path);
		}
		if (*paths == ':')
			paths++;
	}
	return (NULL);
}

char	*path_find(t_cmd_m *cmd, t_env_m *env)
{
	char	*buff;
	char	*path;
	char	*paths;

	path = cmd->argv->content;
	paths = env_get(env, "PATH");
	if (!paths || *paths == '\0')
	{
		path = ft_strdup(path);
		if (!path)
		{
			perror("minishell: path_find: ft_strdup");
			exit_on_failure(cmd, NULL, NULL, env);
		}
		return (path);
	}
	buff = malloc(ft_strlen(paths) + ft_strlen(path) + 2);
	if (!buff)
	{
		perror("minishell: cmd_path");
		exit_on_failure(cmd, NULL, NULL, env);
	}
	path = path_find_loop(paths, buff, cmd, env);
	free(buff);
	return (path);
}

char	*cmd_path(t_cmd_m *cmd, t_env_m *env)
{
	char	*path;

	path = cmd->argv->content;
	if (!path || *path == '\0')
		return (NULL);
	if (*path == '.' && *(path + 1) == '\0')
	{
		fd_printf(STDERR_FD, "%s: %s\n", path, "filename argument required");
		fd_printf(STDERR_FD, ".: usage: . filename [arguments]");
		minishell_free(cmd, NULL, NULL, env);
		exit(2);
	}
	if (ft_strchr(path, '/'))
	{
		path = ft_strdup(path);
		if (!path)
		{
			perror("minishell: cmd_path: strndup");
			exit_on_failure(cmd, NULL, NULL, env);
		}
		return (path);
	}
	return (path_find(cmd, env));
}
