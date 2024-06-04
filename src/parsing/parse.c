/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:21:41 by stephane          #+#    #+#             */
/*   Updated: 2024/06/04 11:00:05 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*parse_spl_quoted(t_buff *buffer, char *str)
{
	char	*temp;

	str++;
	temp = str;
	while (*temp != '\'')
		temp++;
	if (buff_add_str_n(buffer, str, temp - str) == FAILURE)
		return (NULL);
	temp++;
	return (temp);
}

char	*parse_dbl_quoted(t_buff *buffer, char *str, t_env *env)
{
	str++;
	while (*str != '\"')
	{
		if (*str == '$')
		{
			str = expanse_quoted(buffer, ++str, env);
			if (!str)
				return (NULL);
		}
		else if (buff_add_char(buffer, *str++) == FAILURE)
			return (NULL);
	}
	str++;
	return (str);
}
