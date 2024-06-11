/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_dequote_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 23:18:52 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 02:53:13 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_and_dequote_bonus.h"

char	*handle_wildcard(t_tmpdata *data, char *str)
{
	if ((data->wc.list == NULL) && (buff_len(&data->buffer) == 0))
		data->wc.flags |= WILDCARD_FIRST;
	if (data_buffer_to_wclist(data) == FAILURE)
		return (NULL);
	data->wc.flags |= WILDCARD_LAST;
	if (buff_add_char(&data->format, '*') == FAILURE)
		return (NULL);
	return (++str);
}

t_bool	split_word(char *str, t_tmpdata *data, t_list **argv)
{
	while (*str)
	{
		if (is_blank(*str))
		{
			if (select_with_data(data, argv) == FAILURE)
				return (FAILURE);
			while (is_blank(*str))
				str++;
		}
		while (*str && !is_blank(*str))
		{
			if (*str == '*')
				str = handle_wildcard(data, str);
			else if (data_add_char(data, *str++) == FAILURE)
				return (FAILURE);
		}
	}
	return (SUCCESS);
}

char	*expanse_unquoted(t_tmpdata *data, char *str, t_list **argv, t_env *env)
{
	char	*end;

	if (*str == '\'' || *str == '\"')
		return (str);
	if (is_special_parameter(*str))
		return (expanse_special_parameter(data, str, env));
	end = end_name(str);
	if (end == str)
	{
		if (data_add_char(data, '$') == FAILURE)
			return (NULL);
		return (str);
	}
	str = env_get_n(env, str, end - str);
	if (!str)
		return (end);
	if (split_word(str, data, argv) == FAILURE)
		return (NULL);
	return (end);
}

t_bool	expand_and_dequote(char *str, t_list **strlist, t_env *env)
{
	t_tmpdata	data;

	if (is_token_empty(str, env))
		return (SUCCESS);
	data_init(&data);
	while (str && *str)
	{
		if (*str == '\'')
			str = expand_spl_quoted(&data, str);
		else if (*str == '\"')
			str = expand_dbl_quoted(&data, str, env);
		else if (*str == '$')
			str = expanse_unquoted(&data, ++str, strlist, env);
		else if (*str == '*')
			str = handle_wildcard(&data, str);
		else if (data_add_char(&data, *str++) == FAILURE)
			str = NULL;
	}
	if (data_buffer_to_wclist(&data) == FAILURE)
		str = NULL;
	if (str && select_with_data(&data, strlist) == SUCCESS)
		return (SUCCESS);
	data_clear(&data);
	ft_lstclear(strlist, free);
	return (FAILURE);
}
