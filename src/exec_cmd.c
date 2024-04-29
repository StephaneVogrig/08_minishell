/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:22:47 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/29 22:34:35 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"

t_bool	redir_cmd(t_redir *redirs)
{
	int		fd;
	int		fd_dup;

	while (redirs)
	{
		fd_dup = STDOUT_FD;
		if (redirs->type == REDIR_IN || redirs->type == HEREDOC)
		{
			fd_dup = STDIN_FD;
			fd = open(redirs->file_name, O_RDONLY);
		}
		else if (redirs->type == REDIR_OUT_APD)
			fd = open(redirs->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redirs->type == REDIR_OUT_TRC)
			fd = open(redirs->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			fd_printf(STDERR_FD, "minishell: %s: %s\n", redirs->file_name, strerror(errno));
			return (FAILURE);
		}
		dup2(fd, fd_dup);
		close(fd);
		redirs = redirs->next;
	}
	return (SUCCESS);
}

void	exec_cmd(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**argv;
	char	**envp;

	if (!redir_cmd(cmd->redir))
	{
		pipeline_free(&cmd);
		exit(EXIT_FAILURE);
	}
	argv = strlist_to_strtab(cmd->argv);
	cmd->argv = NULL;
	pipeline_free(&cmd);
	if (!argv)
		exit_on_failure(NULL, NULL, env);
	path = cmd_path(argv, env);
	if (!path)
		exit_on_failure(NULL, argv, env);
	envp = env_to_envp(env);
	if (!envp)
		exit_on_failure(NULL, argv, env);
	execve(path, argv, envp);
	perror("minishell");
	strtab_free(envp);
	exit_on_failure(path, argv, NULL);
}
