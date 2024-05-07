/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:52:14 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/07 04:11:36 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

t_bool	is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}

t_bool	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (TRUE);
	return (FALSE);
}

char	*skip_blank(char *str)
{
	if (!str)
		return (NULL);
	while (is_blank(*str))
		str++;		
	return (str);	
}

void	pipex_strncpy(char *dest, char *src, int n)
{
	while (n-- && *src)
		*dest++ = *src++;
	*dest = '\0';
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
