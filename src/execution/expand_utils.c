/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 23:00:13 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/10 01:33:38 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_and_dequote.h"

char	*expanse_special_parameter(t_buff *buffer, char *str, t_env *env)
{
	char	*value;

	value = env_get_n(env, str, 1);
	if (buff_add_str(buffer, value) == FAILURE)
		return (NULL);
	return (++str);
}

char	*expanse_quoted(t_buff *buffer, char *str, t_env *env)
{
	char	*end;

	if (is_special_parameter(*str))
		return (expanse_special_parameter(buffer, str, env));
	end = end_name(str);
	if (end == str)
	{
		if (buff_add_char(buffer, '$') == FAILURE)
			return (NULL);
		return (str);
	}
	str = env_get_n(env, str, end - str);
	if (str && buff_add_str(buffer, str) == FAILURE)
		return (NULL);
	return (end);
}

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
