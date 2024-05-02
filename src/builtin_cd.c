/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:27:39 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/02 21:22:21 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "environment.h"
#include <limits.h>

// int	cd_for_test(t_env *env, char *str)
// {
// 	if (!str) // cd seul -> on va dans la maison
// 		return (go_home(env));
// 	if (str[0] == '\0') // chaine vide
// 		return (0);
// 	if ((str[0] == '~' && str[1] == '\0'))
// 		return (go_home(env));
// 	else
// 		return (change_dir(env, str));
// }

void	print_path(void) // for test
{
	char *str;
	char buffer[PATH_MAX];

	str = getcwd(buffer, PATH_MAX);
	// printf("print path -> %s\n", str);
}

int	uptdate_PWD_OLPWD(t_env *env)
{
	t_env	*node;
	char	*str;
	char	buffer[PATH_MAX];

	str = env_get(env, "PWD");
	node = env_get_node_n(env, "OLDPWD", 6);
	// printf("node= %p\n", node); // test
	if (!node)
		return (1);
	free(node->value);
	node->value = ft_strdup(str);
	if (!node->value)
		return (ENOMEM);
	str = getcwd(buffer, PATH_MAX);
	node = env_get_node_n(env, "PWD", 3);
	if (!node)
		return (1);
	// printf("node->value= %s\n", node->value);
	free(node->value);
	node->value = ft_strdup(str);
	if (!node->value)
		return (ENOMEM);
	return (0);
}

int	go_home(t_env *env, char c)
{
	int		ret;
	char	*str;

	// printf("fonction go_home \n");
	// str = env_get(env, "HOME");
	print_path();
	if (c != '~')
		str = getenv("HOME");
	else
		str = env_get(env, "HOME_cpy");
	printf("-> str HOME: %s\n", str);
	if (!str)
	{
		ft_printf("bash: cd: HOME not set\n");
		return (1);
	}
	ret = chdir(str);
	if (ret == -1)
	{
		perror("");
		exit(1);
	}
	return (uptdate_PWD_OLPWD(env)); // modif valeurs PWD + OLDPWD dans env
}

int	change_dir(t_env *env, char *str)
{
	int	ret;

	// printf("-> str: %s\n", str);
	ret = chdir(str); // on bouge dans le nouveau chemin
	// printf("-> ret: %d\n", ret);
	if (ret == -1)
	{
		perror("");
		return (1);
	}
	// print_path();                    // for test
	return (uptdate_PWD_OLPWD(env)); // modif valeurs PWD + OLDPWD dans env
}

static int	cd(t_env *env, t_cmd *cmd)
{
	t_list	*argv;
	char	*str;

	str = NULL;
	argv = cmd->argv;
	argv = argv->next;
	if (argv)
		str = argv->content;
	printf("->str = %s \n", str);
	if (!argv)
		return (go_home(env, ' '));
	if (str[0] == '\0') // en attente modif parsing
		return (0);
	if ((str[0] == '~' && str[1] == '\0'))
		return (go_home(env, '~'));
	else
		return (change_dir(env, str));
}

int	builtin_cd(t_cmd *cmd, t_env *env)
{
	int	error;

	if (!env)
		return (0);
	error = cd(env, cmd);
	if (error == ENOMEM)
	{
		cmd_free(cmd);
		env_free(env);
		exit(EXIT_FAILURE);
	}
	return (error);
}
