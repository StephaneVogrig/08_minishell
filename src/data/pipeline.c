/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 03:11:28 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/07 01:37:22 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

t_cmd	*pipeline_clear_first(t_cmd *pipeline)
{
	t_cmd	*temp;

	temp = pipeline->next;
	// cmd_free(pipeline);
	return (temp);
}

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
