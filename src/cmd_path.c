/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:36:25 by stephane          #+#    #+#             */
/*   Updated: 2024/05/05 07:50:04 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_path.h"

char	*cmd_path_strndup(char *str, int n)
{
	char	*dup;

	dup = ft_strndup(str, n);
	if (!dup)
		perror("minishell: cmd_path_strndup");
	return (dup);
}

void	check_path(char *path, t_char_m **argv, t_env_m *env)
{
	char	*temp;

	if (path)
		temp = path;
	else
		temp = *argv;
	if (is_directory(temp))
	{
		fd_printf(STDERR_FD, "minishell: %s: is a directory\n", temp);
		minishell_free(path, argv, env);
		exit(126);
	}
	if (access(temp, X_OK) == -1)
	{
		fd_printf(STDERR_FD, "minishell: %s: %s\n", temp, strerror(errno));
		minishell_free(path, argv, env);
		exit(127);
	}
}

char	*path_find(char	*paths, t_char_m *buff, t_char_m **argv, t_env_m *env)
{
	char	*temp;

	while (*paths)
	{
		temp = buff;
		while (*paths && *paths != ':')
			*temp++ = *paths++;
		*temp++ = '/';
		strcpy_offset(temp, *argv);
		if (access(buff, F_OK) == 0)
		{
			check_path(buff, argv, env);
			return (cmd_path_strndup(buff, ft_strlen(buff)));
		}
		if (*paths == ':')
			paths++;
	}
	return (NULL);
}

char	*cmd_path(t_char_m **argv, t_env_m *env)
{
	char	*buff;
	char	*path;

	if (**argv == '\0')
		exit_on_cmd_not_found(argv, env);
	path = env_get(env, "PATH");
	if (!path || ft_strchr(*argv, '/'))
	{
		if (access(*argv, F_OK) != 0)
			exit_on_cmd_not_found(argv, env);
		check_path(NULL, argv, env);
		return (cmd_path_strndup(*argv, ft_strlen(*argv)));
	}
	buff = malloc(ft_strlen(path) + ft_strlen(*argv) + 2);
	if (!buff)
	{
		perror("minishell: cmd_path");
		return (NULL);
	}
	path = path_find(path, buff, argv, env);
	free(buff);
	if (!path)
		exit_on_cmd_not_found(argv, env);
	return (path);
}
