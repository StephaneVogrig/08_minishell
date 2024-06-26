/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:14:20 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/13 02:02:34 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_builtin	builtin_function(t_list *argv)
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

static void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	exit_minishell(t_cmd *cmd, t_env *env)
{
	int	exit_code;

	exit_code = exit_status_get_int(env);
	if (shell_mode_is_interactive(env))
		rl_clear_history();
	minishell_free(cmd, NULL, NULL, env);
	exit(exit_code);
}

int	exec_builtin_alone(t_builtin builtin, t_cmd *cmd, t_env **env, t_cmd *data)
{
	int	fd[2];
	int	exit_code;

	fd[0] = dup(0);
	fd[1] = dup(1);
	exit_code = exec_redir(cmd->redir, *env);
	if (exit_code == FAILURE)
	{
		close_fd(fd);
		return (EXIT_FAILURE);
	}
	else if (exit_code == SUCCESS)
		exit_code = builtin(cmd, env);
	else
		exit_code = EXIT_FAILURE;
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close_fd(fd);
	if (builtin == &builtin_exit && exit_code < 0)
		exit_minishell(data, *env);
	return (exit_code);
}
