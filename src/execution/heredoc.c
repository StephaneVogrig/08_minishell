/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:15:30 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/19 20:21:51 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

int	heredoc_loop(t_cmd_m *cmdlist)
{
	int		exit_code;
	t_redir	*redir;

	exit_code = EXIT_SUCCESS;
	while (cmdlist)
	{
		redir = cmdlist->redir;
		while (redir)
		{
			if (redir->type & HEREDOC)
			{
				exit_code = heredoc_fill(redir);
				if (exit_code != EXIT_SUCCESS)
					return (exit_code);
			}
			redir = redir->next;
		}
		cmdlist = cmdlist->next;
	}
	return (exit_code);
}

t_bool	heredoc(t_cmd_m *cmdlist, t_env *env)
{
	int		exit_code;

	signal(SIGINT, handler_ctrl_c_heredoc);
	exit_code = heredoc_loop(cmdlist);
	if (exit_code != EXIT_SUCCESS)
		pipeline_free(&cmdlist);
	if (shell_mode_is_interactive(env))
		signal(SIGINT, handler_ctrl_c_interactive);
	else
		signal(SIGINT, handler_ctrl_c_file);
	return (exit_code);
}
