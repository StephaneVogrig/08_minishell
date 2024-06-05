/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_wait.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:19:24 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/05 17:55:44 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline_wait.h"
#include "libft.h"

int	wait_process(t_cmd *cmd)
{
	int	wstatus;
	int	exit_code;

	wstatus = 0;
	exit_code = EXIT_SUCCESS;
	while (cmd)
	{
		if (cmd->pid > 0)
			waitpid(cmd->pid, &wstatus, 0);
		cmd = cmd->next;
	}
	if (WIFEXITED(wstatus))
		exit_code = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		exit_code = 128 + WTERMSIG(wstatus);
	return (exit_code);
}
