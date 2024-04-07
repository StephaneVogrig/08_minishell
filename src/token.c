/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 00:11:51 by stephane          #+#    #+#             */
/*   Updated: 2024/04/06 23:46:49 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char	*str_to_token(char *str, char *token)
{
	char	quote;

	while (*str && !is_blank(*str) && !is_operator(*str))
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str++;
			while (*str && *str != quote)
				*token++ = *str++;
			if (*str)
				str++;
			continue ;
		}
		*token++ = *str++;
	}
	*token = '\0';
	return (str);
}

int	len_next_token(char *str)
{
	int		size;
	char	quote;

	size = 0;
	while (*str && !is_blank(*str) && !is_operator(*str))
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str++;
			while (*str && *str++ != quote)
				size++;
			if (*str)
				str++;
			continue ;
		}
		str++;
		size++;
	}
	return (size);
}

char	*next_token(char *str, char	**token)
{
	*token = malloc(len_next_token(str) + 1);
	if (!*token)
	{
		perror("minishell: next_token");
		return (NULL);
	}
	str = str_to_token(str, *token);
	return (str);
}

char	*add_next_token(char *str, t_list **tokenlist)
{
	char	*token;

	str = next_token(str, &token);
	if(!str)
		return (NULL);
	if (!add_to_strlist(tokenlist, token))
		return (NULL);
	return (str);
}