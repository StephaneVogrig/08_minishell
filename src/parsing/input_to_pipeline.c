/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:25:18 by stephane          #+#    #+#             */
/*   Updated: 2024/06/02 18:36:51 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "input_to_pipeline.h"

char	*new_current_cmd(t_cmd **cmd, char *str)
{
	t_cmd	*new;	

	new = cmd_new();
	if (!new)
		return (NULL);
	new->previous = *cmd;
	(*cmd)->next = new;
	*cmd = new;
	return (++str);
}

char	*parse(char *input, t_cmd **cmd)
{
	if (*input == '|')
		return (new_current_cmd(cmd, input));
	if (*input == '<' && *(input + 1) == '<')
		return (next_token_to_heredoc(input + 2, &(*cmd)->redir));
	if (*input == '>' || *input == '<')
		return (next_token_to_redir(input, &(*cmd)->redir));
	return (next_token_to_arglist(input, &((*cmd)->argv)));
}

t_cmd	*input_to_pipeline(char *input)
{
	t_cmd	*pipeline;
	t_cmd	*cmd;

	cmd = cmd_new();
	if (!cmd)
		return (NULL);
	pipeline = cmd;
	while (*input)
	{
		input = parse(input, &cmd);
		if (!input)
		{
			pipeline_free(&pipeline);
			return (NULL);
		}
		input = skip_blank(input);
	}
	if (!cmd->next && !cmd->redir && !cmd->argv && !cmd->previous)
	{
		free(cmd);
		return (NULL);
	}
	return (pipeline);
}
