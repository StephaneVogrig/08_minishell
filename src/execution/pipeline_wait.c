/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_wait.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:19:24 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/28 11:59:41 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	return (exit_code);
}
