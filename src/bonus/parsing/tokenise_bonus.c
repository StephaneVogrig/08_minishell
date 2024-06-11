/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:09:48 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 14:59:20 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenise_bonus.h"

t_bool	compact_redir(t_tokenlist *tokens)
{
	t_tokenlist	*next;

	while (tokens)
	{
		if (tokens->type & REDIR)
		{
			next = tokens->next;
			if (!next)
				return (syntax_error_msg_token(NULL));
			if (next->type != WORD)
				return (syntax_error_msg_token(next));
			tokens->str = next->str;
			tokens->next = next->next;
			free(next);
		}
		tokens = tokens->next;
	}
	return (SUCCESS);
}

char	*tokenise_parse(char *str, t_tokenlist **tokens)
{
	if (*str == ';')
		return (tokenise_add(str, tokens, SEMI_COLON));
	if (*str == '(')
		return (tokenise_add(str, tokens, PARENTHESIS_OPEN));
	if (*str == ')')
		return (tokenise_add(str, tokens, PARENTHESIS_CLOSE));
	if (*str == '&')
		return (tokenise_and(str, tokens));
	if (*str == '|')
		return (tokenise_pipe(str, tokens));
	if (*str == '<' || *str == '>')
		return (tokenise_redir(str, tokens));
	return (tokenise_word(str, tokens));
}

t_tokenlist_m	*tokenise(char *str)
{
	t_tokenlist	*tokens;

	tokens = NULL;
	errno = 0;
	while (*str)
	{
		while (is_blank(*str))
			*str++ = '\0';
		if (*str == '\0')
			return (tokens);
		str = tokenise_parse(str, &tokens);
		if (str)
			continue ;
		tokenlist_free(tokens);
		return (NULL);
	}
	if (compact_redir(tokens) == SUCCESS)
		return (tokens);
	tokenlist_free(tokens);
	return (NULL);
}
