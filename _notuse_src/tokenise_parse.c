/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 00:00:20 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 14:48:19 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenise_bonus.h"

char *token_type_to_str(int token_type)
{
	if (token_type & HEREDOC)
		return ("<<");
	else if (token_type & APPEND)
		return (">>");
	else if (token_type & IN)
		return ("<");
	else if (token_type & OUT)
		return (">");
	return ("|");
}

char	*tokenise_parse(char *str, t_tokenlist **tokens)
{
		if (*str == '|')
			return (token_add(str, tokens, PIPE));
		if (*str == '<' || *str == '>')
			return (tokenise_redir(str, tokens));
		return (tokenise_word(str, tokens));
}
