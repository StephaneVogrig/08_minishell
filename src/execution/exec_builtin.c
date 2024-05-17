/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:14:20 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/17 21:44:48 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int (*builtin_function(t_list *argv))(t_cmd *, t_env *)
{
	if (!argv)
		return (NULL);
	if (!ft_strcmp(argv->content, "export"))
		return (&builtin_export);
	if (!ft_strcmp(argv->content, "unset"))
		return (&builtin_unset);
	if (!ft_strcmp(argv->content, "env"))
		return (&builtin_env);
	if (!ft_strcmp(argv->content, "pwd"))
		return (&builtin_pwd);
	if (!ft_strcmp(argv->content, "cd"))
		return (&builtin_cd);
	if (!ft_strcmp(argv->content, "echo"))
		return (&builtin_echo);
	if (!ft_strcmp(argv->content, "exit"))
		return (&builtin_exit);
	return (NULL);
}

int	exec_builtin_alone(t_builtin builtin, t_cmd *cmd, t_env *env)
{
	int	fd[2];
	int	exit_code;

	fd[0] = dup(0);
	fd[1] = dup(1);
	if (exec_redir(cmd->redir))
		exit_code = builtin(cmd, env);
	else
		exit_code = EXIT_FAILURE;
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	return (exit_code);
}
