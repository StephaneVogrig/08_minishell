/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:15:30 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/19 20:46:53 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "pipelist_bonus.h"

int	heredoc_cmd(t_cmd_m *cmd)
{
	int		exit_code;
	t_redir	*redir;

	exit_code = EXIT_SUCCESS;
	redir = cmd->redir;
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
	if (cmd->flag & SUB)
		exit_code = heredoc_loop(cmd->pipelist);
	return (exit_code);
}

int	heredoc_loop(t_cmd *pipelist)
{
	int		exit_code;
	t_cmd	*pipeline;

	exit_code = EXIT_SUCCESS;
	while (pipelist)
	{
		pipeline = pipelist->pipeline;
		while (pipeline)
		{
			exit_code = heredoc_cmd(pipeline);
			if (exit_code != EXIT_SUCCESS)
				return (exit_code);
			pipeline = pipeline->next;
		}
		pipelist = pipelist->next;
	}
	return (EXIT_SUCCESS);
}

t_bool	heredoc(t_cmd_m *pipelist, t_env *env)
{
	int		exit_code;

	signal(SIGINT, handler_ctrl_c_heredoc);
	exit_code = heredoc_loop(pipelist);
	if (shell_mode_is_interactive(env))
		signal(SIGINT, handler_ctrl_c_interactive);
	else
		signal(SIGINT, handler_ctrl_c_file);
	return (exit_code);
}
