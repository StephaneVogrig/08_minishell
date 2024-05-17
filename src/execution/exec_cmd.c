/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:22:47 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/17 21:44:32 by svogrig          ###   ########.fr       */
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

	while (redirs)
	{
		fd = redir_open(redirs->str, redirs->type);
		if (fd == -1)
		{
			fd_printf(STDERR_FD, "minishell: %s: %s\n", redirs->str,
				strerror(errno));
			redirlist_unlink_heredoc(redirs);
			return (FAILURE);
		}
		if (redirs->type & IN)
			dup2(fd, STDIN_FD);
		else
			dup2(fd, STDOUT_FD);
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

	if (!cmd->argv)
	{
		minishell_free(cmd, NULL, NULL, env);
		exit(EXIT_SUCCESS);
	}
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
	signal(SIGINT, SIG_DFL);
	execve(path, argv, envp);
	perror("minishell: exec_cmd");
	strtab_free(envp);
	exit_on_failure(NULL, path, argv, env);
}
