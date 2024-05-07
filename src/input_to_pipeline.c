/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:25:18 by stephane          #+#    #+#             */
/*   Updated: 2024/05/07 06:31:04 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*parse(char *input, t_cmd **cmd, t_env *env, int *exit_status)
{
	if (*input == '|')
		return (new_current_cmd(cmd, input));
	if (*input == '<' && *(input + 1) == '<')
		return (next_token_to_heredoc(input + 2, &(*cmd)->redir));
	if (*input == '>' | *input == '<')
		return (next_token_to_redir(input, &(*cmd)->redir, env, exit_status));
	return (next_token_to_srtlist(input, &((*cmd)->argv), env, exit_status));
}

t_cmd	*input_to_pipeline(char *input, t_env *env, int *exit_status)
{
	t_cmd	*pipeline;
	t_cmd	*current_cmd;

	current_cmd = cmd_new();
	if (!current_cmd)
		return (NULL);
	pipeline = current_cmd;
	while (*input)
	{
		input = parse(input, &current_cmd, env, exit_status);
		if (!input)
		{
			pipeline_free(&pipeline);
			return (NULL);
		}
		input = skip_blank(input);
	}
	return (pipeline);
}
