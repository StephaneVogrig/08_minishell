/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:23:08 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/01 22:41:19 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// static int	env(char **envp)
// {
// 	// env sans arg return=0
// 	// env avec arg doit etre chemin acces
// 	// si existe pas->127,si acces refuse->126
// 	if (envp == NULL)
// 		return (127);
// 	while (*envp)
// 	{
// 		if (ft_strchr(*envp, '='))
// 		{
// 			ft_putstr_fd(*envp, STDOUT_FD);
// 			write(STDOUT_FD, "\n", 1);
// 		}
// 		envp++;
// 	}
// 	return (0);
// }

static int	env(t_env *env, char *str)
{
	// env sans arg return=0
	// env avec arg doit etre chemin acces
	// si existe pas->127,si acces refuse->126
	if (env == NULL)
		return (127);
	if (!access(str, X_OK))
		return (126);
	display_the_list(env, EXPORTED);
	return (0);
}

int	builtin_env(t_cmd *cmd, t_env *envp)
{
	t_list	*argv;
	int		error;
	int		ret;

	ret = 0;
	// if (!env)
	// 	return (0);
	argv = cmd->argv;
	argv = argv->next;
	// if (!argv)
	// 	return (display_envp_sorted(env));
	error = env(envp, argv->content);
	if (error == ENOMEM)
	{
		cmd_free(cmd);
		env_free(envp);
		exit(EXIT_FAILURE);
	}
	return (error);
}
