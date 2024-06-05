/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:59:27 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/04 18:40:15 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*new_bonus_cmd(char *str, t_cmd **cmd, int type)
{
	t_cmd	*new;
	// ft_printf("new bonus cmd, type = %i\n", type);
	new = cmd_new();
	if (!new)
	{
		perror("minishell: new_bonus_cmd");
		return (NULL);
	}
	new->previous = *cmd;
	// ft_printf("new->flag=%d\n", new->flag);

	
	new->flag = type;
	// ft_printf("new->flag=%d\n", new->flag);
	(*cmd)->next = new;
	*cmd = new;
	return (++str);
}

char	*parse(char *input, t_cmd **cmdlist)
{
	t_cmd	*pipeline;

	if (!(*cmdlist)->pipeline)
		(*cmdlist)->pipeline = cmd_new();
	pipeline = (*cmdlist)->pipeline;
	while (pipeline->next)
		pipeline = pipeline->next;


	if (*input == ';')
		return (new_bonus_cmd(input, cmdlist, 0));
	if (*input == '&' && *(input + 1) == '&')
{
		return (new_bonus_cmd(++input, cmdlist, AND));
}
	if (*input == '|' && *(input + 1) == '|')
		return (new_bonus_cmd(++input, cmdlist, OR));
	if (*input == '|')
		return (new_current_cmd(&pipeline, input));
	if (*input == '<' && *(input + 1) == '<')
		return (next_token_to_heredoc(input + 2, &pipeline->redir));
	if (*input == '>' || *input == '<')
		return (next_token_to_redir(input, &pipeline->redir));
	return (next_token_to_arglist(input, &pipeline->argv));
}
