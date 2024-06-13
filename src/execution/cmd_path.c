/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:36:25 by stephane          #+#    #+#             */
/*   Updated: 2024/06/13 16:23:19 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_path.h"

char	*path_exsting(char *buffer, t_env *env, t_cmd *data)
{
	struct stat	buf;
	char		*path;

	if (stat(buffer, &buf) != 0 || !(S_ISREG(buf.st_mode)))
		return (NULL);
	path = ft_strdup(buffer);
	if (!path)
	{
		perror("minishell: path_loop: ft_strdup");
		exit_on_failure(data, buffer, NULL, env);
	}
	return (path);
}

char	*path_loop(char *paths, char *input, t_env *env, t_cmd *data)
{
	char	*buff;
	char	*path;

	buff = malloc(ft_strlen(paths) + ft_strlen(input) + 2);
	if (!buff)
	{
		perror("minishell: cmd_path");
		exit_on_failure(data, NULL, NULL, env);
	}
	while (*paths)
	{
		path = buff;
		while (*paths && *paths != ':')
			*path++ = *paths++;
		*path++ = '/';
		path = strcpy_offset(path, input);
		path = path_exsting(buff, env, data);
		if (path)
			break ;
		if (*paths == ':')
			paths++;
	}
	free(buff);
	return (path);
}

char	*path_find(t_cmd_m *cmd, t_env_m *env, t_cmd *data)
{
	char		*path;
	char		*paths;

	paths = env_get(env, "PATH");
	if (!paths || *paths == '\0')
	{
		path = ft_strdup(cmd->argv->content);
		if (!path)
		{
			perror("minishell: path_find: ft_strdup");
			exit_on_failure(data, NULL, NULL, env);
		}
		return (path);
	}
	path = path_loop(paths, cmd->argv->content, env, data);
	return (path);
}

char	*cmd_path(t_cmd_m *cmd, t_env_m *env, t_cmd *data)
{
	char	*path;

	path = cmd->argv->content;
	if (!path || *path == '\0')
		return (NULL);
	if (*path == '.' && *(path + 1) == '\0')
	{
		fd_printf(STDERR_FD, "minishell: %s: filename argument required\n",
			path);
		fd_printf(STDERR_FD, ".: usage: . filename [arguments]\n");
		minishell_free(data, NULL, NULL, env);
		exit(2);
	}
	if (ft_strchr(path, '/'))
	{
		path = ft_strdup(path);
		if (!path)
		{
			perror("minishell: cmd_path: strndup");
			exit_on_failure(data, NULL, NULL, env);
		}
		return (path);
	}
	return (path_find(cmd, env, data));
}
