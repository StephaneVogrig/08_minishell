/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:22:47 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/07 05:14:49 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"

int	redir_open(char *str, int type)
{
	int	fd;

	if (type & IN)
		fd = open(str, O_RDONLY);
	else if (type & APPEND)
		fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

t_bool	exec_redir(t_redir *redirs)
{
	int	fd;
	int	fd_dup;

	while (redirs)
	{
		fd = redir_open(redirs->str, redirs->type);
		if (fd == -1)
		{
			fd_printf(STDERR_FD, "minishell: %s: %s\n", redirs->str,
				strerror(errno));
			return (FAILURE);
		}
		if (redirs->type & IN)
			fd_dup = STDIN_FD;
		else
			fd_dup = STDOUT_FD;
		dup2(fd, fd_dup);
		close(fd);
		if (redirs->type & HEREDOC)
			unlink(redirs->str);
		redirs = redirs->next;
	}
	return (SUCCESS);
}

void	exec_cmd(t_cmd_m *cmd, t_env_m *env)
{
	char	*path;
	char	**argv;
	char	**envp;

	if (!exec_redir(cmd->redir))
	{
		redirlist_unlink_heredoc(cmd->redir);
		exit_on_failure(cmd, NULL, NULL, env);		
	}
	if (!cmd->argv)
		exit_on_failure(cmd, NULL, NULL, env);
	argv = argvlist_to_argvtab(&cmd->argv);
	pipeline_free(&cmd);
	if (!argv)
		exit_on_failure(NULL, NULL, NULL, env);
	path = cmd_path(argv, env);
	if (!path)
		exit_on_failure(NULL, NULL, argv, env);
	envp = env_to_envp(env);
	if (!envp)
		exit_on_failure(NULL, path, argv, env);
	execve(path, argv, envp);
	perror("minishell: exec_cmd");
	strtab_free(envp);
	exit_on_failure(NULL, path, argv, env);
}
