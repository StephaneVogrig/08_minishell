/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 03:11:28 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/31 16:15:04 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

void	pipeline_free_from_head(t_cmd **pipeline)
{
	t_cmd	*temp;

	if (!pipeline)
		return ;
	while (*pipeline)
	{
		temp = (*pipeline)->next;
		cmd_free(*pipeline);
		*pipeline = temp;
	}
	*pipeline = NULL;
}

void	pipeline_free(t_cmd **cmd)
{
	if (!cmd || !*cmd)
		return ;
	while ((*cmd)->previous)
		*cmd = (*cmd)->previous;
	pipeline_free_from_head(cmd);
}

t_cmd	*pipeline_add_newcmd(t_cmd **pipeline)
{
	t_cmd	*cmd;
	t_cmd	*temp;

	cmd = cmd_new();
	if (!cmd)
		return (NULL);
	temp = *pipeline;
	while (temp->next)
		temp = temp->next;
	temp->next = cmd;
	return (cmd);
}

t_cmd	*cmdlist_head(t_cmd *cmd)
{
	if (!cmd)
		return (cmd);
	while (cmd->previous)
		cmd = cmd->previous;
	return (cmd);
}

void	redirlist_unlink_heredoc(t_redir *redir)
{
	while (redir)
	{
		if (redir->type & HEREDOC)
			unlink(redir->str);
		redir = redir->next;
	}
}

void	cmdlist_unlink_heredoc(t_cmd *cmd)
{
	cmd = cmdlist_head(cmd);
	while (cmd)
	{
		redirlist_unlink_heredoc(cmd->redir);
		cmd = cmd->next;
	}
}
