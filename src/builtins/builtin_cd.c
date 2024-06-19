/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:27:39 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/19 18:00:32 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	update_pwd_oldpwd(t_env **env_ptr)
{
	char	*str;
	int		type;
	char	buffer[PATH_MAX];

	type = DIR_;
	str = env_get(*env_ptr, "PWD");
	if (!str)
	{
		type = DIR_NO_VAL;
		str = "\0";
	}
	if (env_set_value("OLDPWD", str, *env_ptr) == ENOEXIST)
		if (env_add_new("OLDPWD", str, type, env_ptr) == NULL)
			return (EXIT_FAILURE);
	str = getcwd(buffer, PATH_MAX);
	if (env_set_value("PWD", str, *env_ptr) == ENOEXIST)
		if (env_add_new("PWD", str, type, env_ptr) == NULL)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
	return (update_pwd_oldpwd(env));
}

static int	cd(t_env **env, t_cmd *cmd)
{
	t_list	*argv;
	char	*str;
	char	*msg;

	str = NULL;
	argv = cmd->argv;
	argv = argv->next;
	if (argv)
		str = argv->content;
	if (!argv)
		return (go_home(env, ' '));
	if (str[0] == '\0')
		return (EXIT_SUCCESS);
	if ((str[0] == '~' && str[1] == '\0'))
		return (go_home(env, '~'));
	if (chdir(str) == -1)
	{
		msg = "minishell: cd:";
		fd_printf(STDERR_FILENO, "%s %s: %s\n", msg, str, strerror(errno));
		return (EXIT_FAILURE);
	}
	return (update_pwd_oldpwd(env));
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
	return (error);
}
