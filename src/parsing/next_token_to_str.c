/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_token_to_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:54:29 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 12:18:41 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "next_token_to_str.h"

static int	next_token_len(char *str)
{
	int		len;
	char	quote;

	len = 0;
	while (!is_meta(*str))
	{
		if (*str == '\"' || *str == '\'')
		{
			quote = *str++;
			len++;
			while (*str != quote)
			{
				len++;
				str++;
			}
		}
		len++;
		str++;
	}
	return (len);
}

static char	*next_token_cpy(char *dest, char *src)
{
	char	quote;

	while (!is_meta(*src))
	{
		if (*src == '\"' || *src == '\'')
		{
			quote = *src;
			*dest++ = *src++;
			while (*src != quote)
				*dest++ = *src++;
		}
		*dest++ = *src++;
	}
	*dest = '\0';
	return (src);
}

t_char_m	*next_token_to_str(char **str)
{
	char	*new;

	*str = skip_blank(*str);
	new = ft_calloc(next_token_len(*str) + 1, 1);
	if (!new)
	{
		perror("minishell: next_token_to_str: ft_alloc");
		return (NULL);
	}
	*str = next_token_cpy(new, *str);
	return (new);
}
