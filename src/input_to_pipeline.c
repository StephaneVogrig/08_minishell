/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:25:18 by stephane          #+#    #+#             */
/*   Updated: 2024/04/05 20:21:18 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "input_to_pipeline.h"
#include "command.h"

char	*next_token_to_heredoc(char *str, t_cmd *cmd, t_list **heredocs)
{
	t_list	*new_heredoc;
	
	new_heredoc = ft_listnew(NULL);
	if (!new_heredoc)
	{
		perror("minishell: next_token_to_herdoc: ft_listnew");
		return (NULL);
	}
	str = skip_blank(str);
	str = next_token(str, &(cmd->in));
	if (!str)
		return (NULL);
	cmd->heredoc= new_heredoc;
	ft_lstadd_back(heredocs, new_heredoc);
	return (str);
}

char	*next_token_to_cmdout(char *str, t_cmd *cmd)
{
	if (*str == '>')
	{
		cmd->append_out = TRUE;
		str++;
	}
	else
		cmd->append_out = FALSE;
	str = skip_blank(str);
	str = next_token(str, &(cmd->out));
	return (str);	
}

char	*next_token_to_cmdin(char *str, t_cmd *cmd)
{
	str = skip_blank(str);
	str = next_token(str, &(cmd->in));
	cmd->heredoc = NULL;
	return (str);
}

char	*new_current_cmd(t_cmd **cmd, char *str)
{
	(*cmd)->next =  cmd_new();
	if (!(*cmd)->next)
		return (NULL);
	*cmd = (*cmd)->next;
	return (str);
}

t_list	*parse(char *input, t_cmd **cmd, t_list **heredoc)
{
	if (*input == '|')
		return (new_current_cmd(cmd, input++));
	if (*input == '<' && *(input + 1) == '<')
		return (next_token_to_heredoc(input + 2, *cmd, heredoc));
	if (*input == '<')
		return (nexttoken_to_cmdin(input, *cmd));
	if (*input == '>')
		return (nexttoken_to_cmdout(input + 1, *cmd));
	return (add_next_token(input, &((*cmd)->argv)));
}

t_cmd	*input_to_pipeline(char *input, t_list **heredocs)
{
	t_cmd	*pipeline;
	t_cmd	*cmd;

	cmd = cmd_new();
	if (!cmd)
		return (NULL);
	pipeline = cmd;
	while (*input)
	{
		input = parse(input, &cmd, heredocs);
		if (!input)
		{
			pipeline_free(&pipeline);
			return (NULL);
		}
		input = skip_blank(input);
	}
	return (pipeline);
}
