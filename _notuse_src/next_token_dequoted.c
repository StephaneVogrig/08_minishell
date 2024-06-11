/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_token_dequoted.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 06:42:35 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/31 16:31:12 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "next_token_dequoted.h"

char	*strfill_dequoted(char *input, char **token, t_bool *dequoted)
{
	char	quote;
	char	*dest;

	quote = '\0';
	dest = *token;
	while (!is_meta(*input))
	{
		if (*input == '\'' || *input == '\"')
		{
			quote = *input++;
			while (*input && *input != quote)
				*dest++ = *input++;
			if (*input)
				input++;
			continue ;
		}
		*dest++ = *input++;
	}
	*dest = '\0';
	*dequoted = (quote != '\0');
	return (input);
}

int	strlen_dequoted(char *str)
{
	int		len;
	char	quote;

	len = 0;
	while (!is_meta(*str))
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str++;
			while (*str && *str != quote)
			{
				len++;
				str++;
			}
			if (*str)
				str++;
			continue ;
		}
		len++;
		str++;
	}
	return (len);
}

char	*next_token_dequoted(char *input, char **token, t_bool *dequoted)
{
	int	len;

	len = strlen_dequoted(input);
	*token = malloc(len + 1);
	if (!*token)
	{
		perror("minishell: next_token_unquoted");
		return (NULL);
	}
	input = strfill_dequoted(input, token, dequoted);
	return (input);
}
