/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:59:27 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/04 12:22:37 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*new_bonus_cmd(char *str, t_cmd **cmd, int type)
{
	t_cmd	*new;	
ft_printf("bonus working\n");
	new = cmd_new();
	if (!new)
		return (NULL);
	new->previous = *cmd;
	new->flag = type;
	(*cmd)->next = new;
	*cmd = new;
	return (++str);
}

char	*parse(char *input, t_cmd **cmd)
{
	if (*input == ';')
		return (new_bonus_cmd(input, cmd, 0));
	if (*input == '&' && *(input + 1) == '&')
		return (new_bonus_cmd(++input, cmd, AND));
	if (*input == '|' && *(input + 1) == '|')
		return (new_bonus_cmd(++input, cmd, OR));
	if (*input == '|')
		return (new_current_cmd(cmd, input));
	if (*input == '<' && *(input + 1) == '<')
		return (next_token_to_heredoc(input + 2, &(*cmd)->redir));
	if (*input == '>' || *input == '<')
		return (next_token_to_redir(input, &(*cmd)->redir));
	return (next_token_to_arglist(input, &((*cmd)->argv)));
}
