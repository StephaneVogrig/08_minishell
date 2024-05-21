/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_token_limiter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:07:39 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/21 20:45:17 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "next_token_limiter.h"


char	*strfill_limiter(char *input, char **token, t_bool *dequoted)
{
	char	quote;
	char	*dest;

	quote = '\0';
	dest = *token;
	while (!is_meta(*input))
	{
		if (*input == '$' && (*(input + 1) == '\'' ||  *(input + 1) == '\"'))
			input++;
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

int	strlen_limiteur(char *str)
{
	int		len;
	char	quote;

	len = 0;
	while (!is_meta(*str))
	{
		if (*str == '$' && (*(str + 1) == '\'' ||  *(str + 1) == '\"'))
			str++;
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
			continue;
		}
		len++;
		str++;
	}
	return (len);
}

char	*next_token_to_limiter(char *input, char **token, t_bool *dequoted)
{
	int len;

	len = strlen_limiteur(input);
	*token = malloc(len + 1);
	if	(!*token)
	{
		perror("minishell: next_token_to_limiter");
		return (NULL);
	}
	input = strfill_limiter(input, token, dequoted);
	return (input);
	
}
