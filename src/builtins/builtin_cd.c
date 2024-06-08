/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:27:39 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/08 15:46:59 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "environment.h"
#include <limits.h>

int	uptdate_pwd_oldpwd(t_env **env_ptr)
{
	t_env	*node;
	char	*str;
	char	buffer[PATH_MAX];
	int		type;

	str = NULL;
	type = DIR;
	str = env_get(*env_ptr, "PWD");
	if (!str)
	{
		type = DIR_NO_VAL;
		str = "\0";
	}
	if (env_set_value("OLDPWD", str, *env_ptr) == ENOEXIST)
	{
		node = env_node_new("OLDPWD", str, type);
		env_add_back(env_ptr, node);
	}
	str = getcwd(buffer, PATH_MAX);
	if (env_set_value("PWD", str, *env_ptr) == ENOEXIST)
	{
		node = env_node_new("PWD", str, type);
		env_add_back(env_ptr, node);
	}
	return (0);
}

int	go_home(t_env **env, char c)
{
	int		ret;
	char	*str;

	str = NULL;
	if (c == ' ')
		str = env_get_type(*env, "HOME", EXPORTED);
	else if (c == '~')
		str = env_get_type(*env, "HOME_cpy", INTERNAL);
	if (!str)
	{
		fd_printf(STDERR_FILENO, "minishell: cd: HOME not set\n");
		return (1);
	}
	if (str[0] == '\0')
		return (0);
	ret = chdir(str);
	if (ret == -1)
	{
		perror("");
		exit(1);
	}
	return (uptdate_pwd_oldpwd(env));
}

int	change_dir(t_env **env, char *str)
{
	int	ret;

	ret = chdir(str);
	if (ret == -1)
	{
		fd_printf(STDERR_FILENO, "minishell: cd: %s: ", str);
		perror("");
		return (1);
	}
	return (uptdate_pwd_oldpwd(env));
}

static int	cd(t_env **env, t_cmd *cmd)
{
	t_list	*argv;
	char	*str;

	str = NULL;
	argv = cmd->argv;
	argv = argv->next;
	if (argv)
		str = argv->content;
	if (!argv)
		return (go_home(env, ' '));
	if (str[0] == '\0')
		return (0);
	if ((str[0] == '~' && str[1] == '\0'))
		return (go_home(env, '~'));
	else
		return (change_dir(env, str));
}

int	builtin_cd(t_cmd *cmd, t_env **env)
{
	int		error;
	t_list	*argv;

	if (!env)
		return (0);
	argv = cmd->argv;
	if (ft_lstsize(argv) >= 3)
	{
		fd_printf(STDERR_FD, "cd: too many arguments\n");
		return (1);
	}
	error = cd(env, cmd);
	if (error == ENOMEM)
	{
		cmd_free(cmd);
		env_free(*env);
		exit(EXIT_FAILURE);
	}
	return (error);
}
