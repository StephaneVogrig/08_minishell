/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:14:20 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/05 21:06:43 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int (*builtin_function(char *str))(t_cmd *, t_env *)
{
	if (!ft_strcmp(str, "export"))
		return (&builtin_export);
	if (!ft_strcmp(str, "unset"))
		return (&builtin_unset);
	if (!ft_strcmp(str, "env"))
		return (&builtin_env);
	if (!ft_strcmp(str, "pwd"))
		return (&builtin_pwd);
	if (!ft_strcmp(str, "cd"))
		return (&builtin_cd);
	if (!ft_strcmp(str, "echo"))
		return (&builtin_echo);
	if (!ft_strcmp(str, "exit"))
		return (&builtin_exit);
	return (NULL);
}

t_bool	builtin_is_executed(t_cmd *cmd, t_env *env, int *exit_status)
{
	int (*builtin_ptr)(t_cmd *, t_env *);

	if (!cmd->argv)
		return (FALSE);
	builtin_ptr = builtin_function(cmd->argv->content);
	if (!builtin_ptr)
		return (FALSE);
	if (!exec_redir(cmd->redir))
	{
		pipeline_free(&cmd);
		exit(EXIT_FAILURE);
	}
	*exit_status = builtin_ptr(cmd, env);
	return (TRUE);
}