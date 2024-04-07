/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:47:14 by stephane          #+#    #+#             */
/*   Updated: 2024/04/07 20:16:04 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

t_cmd	*cmd_new(void)
{
	t_cmd	*new;
	
	new = malloc(sizeof(*new));
	if (!new)
	{
		perror("minishell: cmd_new");
		return (NULL);		
	}
	ft_bzero(new, sizeof(*new));
	return (new);
}

void cmd_free(t_cmd *cmd)
{
	if (cmd->redir)
		redirection_free(&cmd->redir);
	if (cmd->argv)
		ft_lstclear(&cmd->argv, free);
	free(cmd);
}

void	pipeline_free(t_cmd **pipeline)
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

t_cmd	*pipeline_add_newcmd(t_cmd **pipeline)
{
	t_cmd	*cmd;
	t_cmd	*temp;
	
	cmd = cmd_new();
	if(!cmd)		
		return (NULL);
	temp = *pipeline;
	while (temp->next)
		temp = temp->next;
	temp->next = cmd;
	return (cmd);
}

int	cmd_nbr(t_cmd *pipeline)
{
	int	i;

	if (!pipeline)
		return (0);
	i = 0;
	while (pipeline)
	{
		pipeline = pipeline->next;
		i++;
	}
	return (i);
}
