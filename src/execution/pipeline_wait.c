/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_wait.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:19:24 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/11 15:38:45 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipeline_wait.h"

int	wait_process(pid_t *pids)
{
	int	wstatus;
	int	exit_code;

	wstatus = 0;
	exit_code = EXIT_SUCCESS;
	while (*pids)
	{
		if (*pids > 0)
			waitpid(*pids, &wstatus, 0);
		pids++;
	}
	if (WIFEXITED(wstatus))
		exit_code = WEXITSTATUS(wstatus);
	return (exit_code);
}
