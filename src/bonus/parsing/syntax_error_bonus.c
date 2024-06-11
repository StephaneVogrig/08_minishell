/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:35:01 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 15:10:40 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_error_bonus.h"

int	check_token(t_tokenlist *token, int *lvl_parenthesis)
{
	if (token->type & WORD || token->type & REDIR)
	{
		if (token->next == NULL)
			return (SUCCESS);
		if (token->next->type == PARENTHESIS_OPEN)
			return (syntax_error_msg_token(token->next));
		return (SUCCESS);
	}
	if (token->type == PARENTHESIS_OPEN)
	{
		*lvl_parenthesis += 1;
		return (check_control(token));
	}
	if (token->type == PARENTHESIS_CLOSE)
		return (check_parenthesis_close(token, lvl_parenthesis));
	if (token->type == SEMI_COLON)
		return (check_semicolon(token));
	if (token->type >= AND)
		return (check_control(token));
	return (SUCCESS);
}

int	check_tokens(t_tokenlist *tokens)
{
	int	lvl_parenthesis;

	lvl_parenthesis = 0;
	if (tokens->type >= SEMI_COLON)
		return (syntax_error_msg_token(tokens));
	while (tokens)
	{
		if (check_token(tokens, &lvl_parenthesis) == SYNTAX_ERROR)
			return (SYNTAX_ERROR);
		tokens = tokens->next;
	}
	if (lvl_parenthesis)
		return (syntax_error_msg_token(NULL));
	return (SUCCESS);
}

t_bool	syntax_error(char *input)
{
	t_tokenlist	*tokens;
	t_bool		error;
	char		*str;

	error = FALSE;
	str = ft_strdup(input);
	if (!str)
	{
		perror("minishell: syntax_error: ft_strdup");
		return (FALSE);
	}
	tokens = tokenise(str);
	if (!tokens)
		return (TRUE);
	error = check_tokens(tokens) == SYNTAX_ERROR;
	tokenlist_free(tokens);
	free(str);
	if (error)
		return (TRUE);
	return (FALSE);
}
