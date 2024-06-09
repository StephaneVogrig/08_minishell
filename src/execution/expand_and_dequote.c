/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_dequote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:14:35 by stephane          #+#    #+#             */
/*   Updated: 2024/06/09 23:07:08 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_and_dequote.h"

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

t_bool	expand_and_dequote(char *str, t_list **strlist, t_env *env)
{
	t_buff	buffer;

	if (is_token_empty(str, env))
		return (SUCCESS);
	buff_init(&buffer);
	while (str && *str)
	{
		if (*str == '\'')
			str = expand_spl_quoted(&buffer, str);
		else if (*str == '\"')
			str = expand_dbl_quoted(&buffer, str, env);
		else if (*str == '$')
			str = expanse_unquoted(&buffer, ++str, strlist, env);
		else if (buff_add_char(&buffer, *str++) == FAILURE)
			str = NULL;
	}
	if (str && strlist_add_buffer(strlist, &buffer) == FAILURE)
		str = NULL;
	buff_clear(&buffer);
	if (str)
		return (SUCCESS);
	ft_lstclear(strlist, free);
	return (FAILURE);
}
