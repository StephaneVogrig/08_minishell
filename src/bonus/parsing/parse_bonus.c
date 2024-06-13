/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:59:27 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/13 04:46:36 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_bonus.h"

char	*end_parenthesis(char *str)
{
	int	open;

	open = 0;
	str++;
	while (*str != ')' || open)
	{
		if (*str == '(')
			open++;
		if (*str == ')')
			open--;
		str++;
	}
	return (str);
}

char	*new_subshell(char *str, t_cmd **cmd)
{
	char	*end;

	end = end_parenthesis(++str);
	*end++ = '\0';
	(*cmd)->pipelist = input_to_pipelist(str);
	if (!(*cmd)->pipelist)
		return (NULL);
	(*cmd)->flag = SUB;
	return (end);
}

char	*new_pipeline(char *str, t_cmd **cmd, t_cmd **pipeline, int type)
{
	t_cmd	*new;

	new = pipelist_new();
	if (!new)
		return (NULL);
	new->previous = *pipeline;
	new->flag = type;
	(*pipeline)->next = new;
	*pipeline = new;
	*cmd = new->pipeline;
	return (++str);
}

char	*parse(char *input, t_cmd **cmd, t_cmd **pipeline)
{
	if (*input == ';')
		return (new_pipeline(input, cmd, pipeline, 0));
	if (*input == '&' && *(input + 1) == '&')
		return (new_pipeline(++input, cmd, pipeline, AND));
	if (*input == '|' && *(input + 1) == '|')
		return (new_pipeline(++input, cmd, pipeline, OR));
	if (*input == '|')
		return (new_current_cmd(cmd, input));
	if (*input == '(')
		return (new_subshell(input, cmd));
	if (*input == '<' && *(input + 1) == '<')
		return (next_token_to_heredoc(input + 2, &(*cmd)->redir));
	if (*input == '>' || *input == '<')
		return (next_token_to_redir(input, &(*cmd)->redir));
	return (next_token_to_arglist(input, &(*cmd)->argv));
}
