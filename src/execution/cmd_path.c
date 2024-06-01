/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:36:25 by stephane          #+#    #+#             */
/*   Updated: 2024/06/01 13:23:06 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_path.h"

t_bool	is_an_existing_file(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == 0 && (S_ISREG(buf.st_mode)))
		return (TRUE);
	return (FALSE);
}

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
		if (is_an_existing_file(buff))
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
	t_char_m	*buff;
	char		*path;
	char		*paths;

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
		fd_printf(STDERR_FD, "minishell: %s: filename argument required\n",
			path);
		fd_printf(STDERR_FD, ".: usage: . filename [arguments]\n");
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
