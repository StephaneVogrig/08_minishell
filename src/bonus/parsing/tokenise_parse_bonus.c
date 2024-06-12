/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_parse_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 23:53:08 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/12 18:25:25 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenise_bonus.h"

char	*tokenise_and(char *str, t_tokenlist **tokens)
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

char	*tokenise_pipe(char *str, t_tokenlist **tokens)
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

char	*tokenise_redir(char *str, t_tokenlist **tokens)
{
	char	redir;
	int		type;

	redir = *str;
	*str++ = '\0';
	if (redir == '<')
		type = (REDIR | IN);
	else
		type = (REDIR | OUT);
	if (*str == redir)
	{
		str++;
		if (redir == '<')
			type |= HEREDOC;
		else
			type |= APPEND;
	}
	if (tokenlist_add(tokens, NULL, type) == FAILURE)
		return (NULL);
	return (str);
}

char	*tokenise_word(char *str, t_tokenlist **tokens)
{
	if (tokenlist_add(tokens, str, WORD) == FAILURE)
		return (NULL);
	while (!is_meta(*str))
	{
		if (*str == '\'' || *str == '\"')
		{
			str = syntax_end_quote(str);
			if (!str)
				return (NULL);
			continue ;
		}
		if (*str == '\0')
			break ;
		str++;
	}
	return (str);
}

char	*tokenise_add(char *str, t_tokenlist **tokens, int type)
{
	*str++ = '\0';
	if (tokenlist_add(tokens, NULL, type) == FAILURE)
		return (NULL);
	return (str);
}
