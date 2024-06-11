/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:52:14 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 16:54:45 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*skip_blank(char *str)
{
	if (!str)
		return (NULL);
	while (is_blank(*str))
		str++;
	return (str);
}

t_char_m	*mini_strndup(char *str, int n)
{
	t_char_m	*new;

	new = ft_strndup(str, n);
	if (!new)
	{
		perror("minishell: mini_strndup");
		return (NULL);
	}
	return (new);
}

t_char_m	*mini_strdup(char *str)
{
	t_char_m	*new;

	new = ft_strdup(str);
	if (!new)
	{
		perror("minishell: mini_strdup");
		return (NULL);
	}
	return (new);
}

char	*end_quote(char *str)
{
	char	quote;

	quote = *str++;
	while (*str && *str != quote)
		str++;
	return (str);
}

t_bool	is_empty(char *str)
{
	str = skip_blank(str);
	if (*str)
		return (FALSE);
	return (TRUE);
}
