/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:22:47 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/07 01:58:52 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "command.h"
#include "stdio.h"//steph

void	exec_cmd(t_cmd *cmd, char **envp)
{
	char	*path;
	char	**argv;
	char	*file_path;
	int		fd_in;
	int		fd_out;

	if (cmd->in)
	{
		file_path = cmd->in;
		fd_in = open(file_path, O_RDONLY);
		if (fd_in == -1)
			exit_on_open_error(file_path, -1);
		dup2(fd_in, STDIN_FD);
		close(fd_in);
	}
	if (cmd->out)
	{
		file_path = cmd->out;
		if (cmd->append_out)
			fd_out = open(file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd_out = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
			exit_on_open_error(file_path, fd_in);
		dup2(fd_out, STDOUT_FD);
		close(fd_out);
	}
	argv = charlist_to_chartab(cmd->argv);
	if (!argv)
		exit(EXIT_FAILURE);
	path = cmd_path(argv, envp);
	if (!path)
	{
		strtab_free(argv);
		exit(EXIT_FAILURE);
	}
	
	execve(path, argv, envp);
	perror("pipex");
	strtab_free(argv);
	free(path);
	exit(EXIT_FAILURE);
}
