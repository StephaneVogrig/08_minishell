/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:19:24 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/06 23:23:31 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline_wait.h"

int	wait_process(pid_t *pids, int n)
{
	int	wstatus;
	int	exit_code;
	int	i;

	wstatus = 0;
	exit_code = EXIT_SUCCESS;
	i = 0;
	while (i <= n)
	{
		if (pids[i] > 0)
			waitpid(pids[i], &wstatus, 0);
		i++;
	}
	if (WIFEXITED(wstatus))
		exit_code = WEXITSTATUS(wstatus);
	return (exit_code);
}
