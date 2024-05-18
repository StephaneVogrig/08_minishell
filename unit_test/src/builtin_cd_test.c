/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:50:40 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/18 15:34:29 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unitest.h"
#include <limits.h>

void	test(t_env *env, char *str)
{
	// char	*path;
	// char	buffer[PATH_MAX];
	printf("--------------------------------------------\n");
	printf("TEST-> env %s\n", str);
	printf("--------------------------------------------\n");
	cd_for_test(env, str);
	// path = getcwd(buffer, PATH_MAX);
	printf("****** NEW ENV ***************\n");
	// printf("current dir -> %s\n", path);
	env_display(env, ALL);
}

void	print_path(void) // for test
{
	char *str;
	char buffer[PATH_MAX];

	str = getcwd(buffer, PATH_MAX);
	printf("print path -> %s\n", str);
}

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

void	builtin_cd_test(char **env)
{
	(void)env;
	char *strtab[] = {"PWD=init", "OLDPWD=init_old", "KEY=un", "KEY=", NULL};

	char *strtab_unset[] = {"KEY=value", "KEY=", NULL};

	t_env *strdup;
	strdup = env_dup(strtab);

	printf("\nSOURCE TAB ----------------------------------\n");
	env_display(strdup, ALL);

	// test(strdup, "NO_EXIST");
	// test(strdup, "../TEST_MiniShell");
	test(strdup, NULL);
	test(strdup, "/nfs/homes/smortemo/Documents/PUSH_EN_COURS/08_minishell");
	// test(strdup, "~");
	// test(strdup, "~test");
	test(strdup, "");

	env_free(strdup);
	printf("____________________________________________\n");
	printf("\n TEST WITH ENV unset PWD OLD_PWD  \n");
	printf("____________________________________________\n");
	printf("\nSOURCE TAB ----------------------------------\n");
	strdup = env_dup(strtab_unset);
	env_display(strdup, ALL);
	print_path();
	test(strdup, "..");
	env_free(strdup);
	printf("____________________________________________\n");
	printf("____________________________________________\n");
}