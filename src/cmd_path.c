/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:36:25 by stephane          #+#    #+#             */
/*   Updated: 2024/04/29 22:32:33 by svogrig          ###   ########.fr       */
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

void	check_path(char *path, char **argv)
{
	char	*temp;

	if (path)
		temp = path;
	else
		temp = *argv;
	if (is_directory(temp))
		exit_on_is_directory(temp, path, argv);
	if (access(temp, X_OK) == -1)
		exit_on_acces_denied(temp, path, argv);
}

char	*path_find(char	*paths, t_char_m *buf, char **argv, int len)
{
	char	*temp;

	while (*paths)
	{
		temp = buf;
		while (*paths && *paths != ':')
			*temp++ = *paths++;
		*temp++ = '/';
		pipex_strncpy(temp, *argv, len);
		if (access(buf, F_OK) == 0)
		{
			check_path(buf, argv);
			temp = cmd_path_strndup(buf, temp + len - buf);
			free(buf);
			return (temp);
		}
		if (*paths == ':')
			paths++;
	}
	free(buf);
	return (NULL);
}

char	*cmd_path(char **argv, t_env *env)
{
	char	*cmd_path;
	char	*paths;
	int		len_cmd;

	if (**argv == '\0')
		exit_on_cmd_not_found(argv, env);
	len_cmd = ft_strlen(*argv);
	paths = env_get(env, "PATH");
	if (!paths || ft_strchr(*argv, '/'))
	{
		if (access(*argv, F_OK) != 0)
			exit_on_cmd_not_found(argv, env);
		check_path(NULL, argv);
		return (cmd_path_strndup(*argv, len_cmd));
	}
	cmd_path = malloc(ft_strlen(paths) + len_cmd + 2);
	if (!cmd_path)
	{
		perror("minishell: cmd_path");
		return (NULL);
	}
	cmd_path = path_find(paths, cmd_path, argv, len_cmd);
	if (!cmd_path)
		exit_on_cmd_not_found(argv, env);
	return (cmd_path);
}
