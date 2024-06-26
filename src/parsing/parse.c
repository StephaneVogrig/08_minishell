/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:21:41 by stephane          #+#    #+#             */
/*   Updated: 2024/06/04 11:09:44 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
