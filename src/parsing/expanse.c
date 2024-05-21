/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:03:55 by stephane          #+#    #+#             */
/*   Updated: 2024/05/21 03:00:35 by svogrig          ###   ########.fr       */
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

char	*expanse_exit_status(t_buff *buffer, char *str, t_env *env)
{
	if (buff_add_str(buffer, env_get(env, "?")) == FAILURE)
			return (NULL);
	return (++str);		
}

char	*expanse_quoted(t_buff *buffer, char *str, t_env *env)
{
	char	*end;
	
	if (*str == '?')
		return (expanse_exit_status(buffer, str, env));
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

	if (*str == '?')
		return (expanse_exit_status(buffer, str, env));
	if (*str == '\'' || *str == '\"')
		return (str);
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
