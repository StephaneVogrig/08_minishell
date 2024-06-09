/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 23:00:13 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/09 23:05:35 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_and_dequote.h"

char	*expand_spl_quoted(t_buff *buffer, char *str)
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

char	*expand_dbl_quoted(t_buff *buffer, char *str, t_env *env)
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

t_bool	is_token_empty(char *str, t_env *env)
{
	char	*end;
	char	*value;

	if (*str != '$')
		return (FALSE);
	while (*str && !is_meta(*str))
	{
		if (*str == '$')
		{
			end = end_name(++str);
			if (end == str)
				return (FALSE);
			value = env_get_n(env, str, end - str);
			if (value && *value)
				return (FALSE);
			str = end;
		}
		else
			return (FALSE);
	}
	return (TRUE);
}
