/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelist_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:14:41 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 15:04:44 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipelist_bonus.h"

t_cmd	*pipelist_new(void)
{
	t_cmd	*pipelist;

	pipelist = cmd_new();
	if (!pipelist)
		return (NULL);
	pipelist->pipeline = cmd_new();
	if (!pipelist->pipeline)
	{
		free(pipelist);
		return (NULL);
	}
	return (pipelist);
}

void	pipeline_free_bonus(t_cmd *cmd)
{
	t_cmd	*temp;

	while (cmd)
	{
		if (cmd->flag == SUB)
		{
			pipelist_free(cmd->pipelist);
			cmd->pipelist = NULL;
		}
		redirection_free(&cmd->redir);
		ft_lstclear(&cmd->argv, free);
		temp = cmd->next;
		free(cmd);
		cmd = temp;
	}
}

void	pipelist_free(t_cmd *pipelist)
{
	t_cmd	*temp;

	while (pipelist)
	{
		pipeline_free_bonus(pipelist->pipeline);
		temp = pipelist->next;
		free(pipelist);
		pipelist = temp;
	}
}
