/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:07:43 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 15:11:16 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_error_bonus.h"

char	*token_type_to_str(int token_type)
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

int	check_parenthesis_close(t_tokenlist	*token, int *lvl_parenthesis)
{
	*lvl_parenthesis -= 1;
	if (lvl_parenthesis < 0)
		return (syntax_error_msg_token(token));
	while (token->next)
	{
		if (token->next->type >= PARENTHESIS_CLOSE)
			return (SUCCESS);
		if (token->next->type == PARENTHESIS_OPEN || token->next->type == WORD)
			return (syntax_error_msg_token(token->next));
		token = token->next;
	}
	return (SUCCESS);
}

int	check_semicolon(t_tokenlist	*token)
{
	if (token->next == NULL)
		return (SUCCESS);
	if (token->next->type >= PARENTHESIS_CLOSE)
		return (syntax_error_msg_token(token->next));
	return (SUCCESS);
}

int	check_control(t_tokenlist	*token)
{
	if (token->next == NULL)
		return (syntax_error_msg_token(NULL));
	return (check_semicolon(token));
}

int	syntax_error_msg_token(t_tokenlist *token)
{
	char	*str;

	if (!token)
		str = "newline";
	else if (token->type == WORD)
		str = token->str;
	else
		str = token_type_to_str(token->type);
	fd_printf(STDERR_FILENO, SYNTAX_ERROR_MSG"`%s'\n", str);
	return (SYNTAX_ERROR);
}
