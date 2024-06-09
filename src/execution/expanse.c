/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:03:55 by stephane          #+#    #+#             */
/*   Updated: 2024/05/31 15:52:34 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanse.h"

char	*end_name(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (str);
	str++;
	while (ft_isalnum(*str) || *str == '_')
		str++;
	return (str);
}

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

t_bool	split_word(char *str, t_buff *buffer, t_list **argv)
{
	while (*str)
	{
		if (is_blank(*str))
		{
			if (strlist_add_buffer(argv, buffer) == FAILURE)
				return (FAILURE);
			buff_clear(buffer);
			while (is_blank(*str))
				str++;
		}
		while (*str && !is_blank(*str))
		{
			if (buff_add_char(buffer, *str) == FAILURE)
				return (FAILURE);
			str++;
		}
	}
	return (SUCCESS);
}

char	*expanse_unquoted(t_buff *buffer, char *str, t_list **argv, t_env *env)
{
	char	*end;

	if (*str == '\'' || *str == '\"')
		return (str);
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
	if (!str)
		return (end);
	if (split_word(str, buffer, argv) == FAILURE)
		return (NULL);
	return (end);
}
