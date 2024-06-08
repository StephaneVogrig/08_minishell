/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:32:26 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/08 19:59:17 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_error.h"

t_bool	syntax_error_msg(char c)
{
	if (c == '\0')
		fd_printf(STDERR_FILENO, SYNTAX_ERROR_MSG"`newline'\n", c);
	else
		fd_printf(STDERR_FILENO, SYNTAX_ERROR_MSG"`%c'\n", c);
	return (TRUE);
}

char	*end_quote(char *str)
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
