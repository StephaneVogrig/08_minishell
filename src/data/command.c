/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:47:14 by stephane          #+#    #+#             */
/*   Updated: 2024/05/28 11:47:46 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "command.h"

t_cmd	*cmd_new(void)
{
	t_cmd	*new;
	
	new = ft_calloc(1, sizeof(*new));
	if (!new)
	{
		perror("minishell: cmd_new");
		return (NULL);		
	}
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

int	cmd_nbr(t_cmd *pipeline)
{
	int	i;

	i = 0;
	while (pipeline)
	{
		pipeline = pipeline->next;
		i++;
	}
	return (i);
}
