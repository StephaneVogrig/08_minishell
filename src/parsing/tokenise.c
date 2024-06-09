/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:09:48 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/09 19:28:43 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenise.h"

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
	else if (token_type == PARENTHESIS_OPEN)
		return ("(");
	else if (token_type == PARENTHESIS_CLOSE)
		return (")");
	else if (token_type == SEMI_COLON)
		return (";");
	else if (token_type == OR)
		return ("||");
	else if (token_type == AND)
		return ("&&");
	return ("|");
}

int	syntax_error_msg_token(t_tokenlist *token)
{
	char *str;
	if (!token)
		str = "newline";
	else if (token->type == WORD)
		str = token->str;
	else
		str = token_type_to_str(token->type);
	fd_printf(STDERR_FILENO, SYNTAX_ERROR_MSG"`%s'\n", str);
	return (SYNTAX_ERROR);
}

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
	while (ft_strchr(" \t|&<>()", *str) == NULL)
	{
		if (*str == '\'' || *str == '\"')
		{
			str = syntax_end_quote(str);
			if (!str)
				return (NULL);
			continue ;
		}
		if (*str == '\0')
			break;
		str++;
	}
	return (str);
}

char	*token_add(char *str, t_tokenlist **tokens, int type)
{
	*str++ = '\0';
	if (tokenlist_add(tokens, NULL, type) == FAILURE)
		return (NULL);
	return (str);
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
		str =  tokenise_parse(str, &tokens);
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
