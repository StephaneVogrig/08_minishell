/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipelist_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 02:36:32 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/07 12:02:18 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_pipelist_bonus.h"
#include "debug.h"

int exec_pipelist(t_cmd *pipelist, t_env **env, t_cmd_m *tofree)
{
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	while (pipelist)
	{	
		if (pipelist->flag == AND && exit_code != EXIT_SUCCESS)
		{
			pipelist = pipelist->next;
			continue ;
		}
		if (pipelist->flag == OR && exit_code == EXIT_SUCCESS)
		{
			pipelist = pipelist->next;
			continue ;
		}
// ft_printf("\nexec_pipelist\n");
// print_pipeline(pipelist->pipeline, NULL);
		exit_code = exec_pipeline(pipelist->pipeline, env, tofree);
		pipelist = pipelist->next;
	}
	return (exit_code);
}
