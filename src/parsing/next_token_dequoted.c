/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_token_dequoted.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 06:42:35 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/07 07:24:54 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "next_token_dequoted.h"

int	strlen_dequoted(char *str)
{
	char	*temp;
	char	quote;

	temp = str;
	while (!is_meta(*str))
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str++;
			while (*str != quote)
				str++;
			str++;
			continue;
		}
		str++;
	}
	return (str - temp);
}

t_bool	strfill_dequoted(char *dest, char *src)
{
	char		quote;

	quote = '\0';
	while (!is_meta(*src))
	{
		if (*src == '\'' || *src == '\"')
		{
			quote = *src++;
			while (*src != quote)
				*dest++ = *src++;
			src++;
			continue ;
		}
		*dest++ = *src++;
	}
	*dest = '\0';
	return (quote != '\0');
}

char *next_token_dequoted(char *input, char **token, t_bool *dequoted)
{
	int len;

	len = strlen_dequoted(input);
	*token = malloc(len + 1);
	if	(!*token)
	{
		perror("minishell: next_token_unquoted");
		return (NULL);
	}
	*dequoted = strfill_dequoted(*token, input);
	return (input + len);
}