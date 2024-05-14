/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:01:52 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/14 19:54:10 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_error.h"

static t_bool	syntax_error_msg(char c)
{
	if (c == '\0')
		fd_printf(STDERR_FD, "minishell: syntax error near unexpected token `newline'\n", c);
	else
		fd_printf(STDERR_FD, "minishell: syntax error near unexpected token `%c'\n", c);
	return (TRUE);
}

static char	*next_token_pipe(char *str)
{
	str++;
	while (is_blank(*str))
		str++;
	if (*str == '\0' || *str == '|')
	{
		syntax_error_msg(*str);
		return (NULL);
	}
	return (str);
}

static char	*next_token_redir(char *str)
{
	char	*ptr;

	ptr = str;
	str++;
	if (*ptr == *str)
		str++;
	while (is_blank(*str))
		str++;
	ptr = ft_strchr("|<>", *str);
	if (ptr)
	{
		syntax_error_msg(*ptr);
		return (NULL);
	}
	return (str);
}

static char	*end_quote(char *str)
{
	char	quote;

	quote = *str;
	str++;
	while (*str)
	{
		if (*str == quote)
			return (++str);
		str++;
	}
	syntax_error_msg('\0');
	return (NULL);
}

t_bool	syntax_error(char *input)
{
	if (*input == '|')
		return (syntax_error_msg('|'));
	while (*input)
	{
		if (*input == '|')
			input = next_token_pipe(input);
		else if (*input == '<' || *input == '>')
			input = next_token_redir(input);
		else if (*input == '\"' || *input == '\'')
			input = end_quote(input);
		else
			input++;
		if (!input)
			return (TRUE);
	}
	return (FALSE);
}
