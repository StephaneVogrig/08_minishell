/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_parse_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 23:53:08 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/09 00:58:53 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenise.h"

static char	*tokenise_and(char *str, t_tokenlist **tokens)
{
	*str++ = '\0';
	if (*str == '&')
	{
		if (tokenlist_add(tokens, NULL, AND) == FAILURE)
			return (NULL);
		return (++str);
	}
	syntax_error_msg('&');
	return (NULL);
}

static char	*tokenise_pipe(char *str, t_tokenlist **tokens)
{
	*str++ = '\0';
	if (*str == '|')
	{
		if (tokenlist_add(tokens, NULL, OR) == FAILURE)
			return (NULL);
		return (++str);
	}
	if (tokenlist_add(tokens, NULL, PIPE) == FAILURE)
		return (NULL);
	return (str);
}

char	*tokenise_parse(char *str, t_tokenlist **tokens)
{
		if (*str == ';')
			return (token_add(str, tokens, SEMI_COLON));
		if (*str == '(')
			return (token_add(str, tokens, PARENTHESIS_OPEN));
		if (*str == ')')
			return (token_add(str, tokens, PARENTHESIS_CLOSE));
		if (*str == '&')
			return (tokenise_and(str, tokens));
		if (*str == '|')
			return (tokenise_pipe(str, tokens));
		if (*str == '<' || *str == '>')
			return (tokenise_redir(str, tokens));
		return (tokenise_word(str, tokens));
}
