/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 23:00:13 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/10 04:29:08 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_and_dequote_bonus.h"

char	*expanse_special_parameter(t_tmpdata *data, char *str, t_env *env)
{
	char	*value;

	value = env_get_n(env, str, 1);
	if (data_add_str(data, value) == FAILURE)
		return (NULL);
	return (++str);
}

char	*expanse_quoted(t_tmpdata *data, char *str, t_env *env)
{
	char	*end;

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
	if (str && data_add_str(data, str) == FAILURE)
		return (NULL);
	return (end);
}

char	*expand_spl_quoted(t_tmpdata *data, char *str)
{
	char	*temp;

	str++;
	temp = str;
	while (*temp != '\'')
		temp++;
	if (data_add_str_n(data, str, temp - str) == FAILURE)
		return (NULL);
	temp++;
	return (temp);
}

char	*expand_dbl_quoted(t_tmpdata *data, char *str, t_env *env)
{
	str++;
	while (*str != '\"')
	{
		if (*str == '$')
		{
			str = expanse_quoted(data, ++str, env);
			if (!str)
				return (NULL);
		}
		else if (data_add_char(data, *str++) == FAILURE)
			return (NULL);
	}
	str++;
	return (str);
}

t_bool	data_buffer_to_wclist(t_tmpdata *data)
{
	char	*str;

	if (buff_len(data->buffer) == 0)
		return (SUCCESS);
	str = buff_to_str(&data->buffer);
	if (!str)
		return (FAILURE);
	if (wc_list_add_str(str, &data->wc) == FAILURE)
	{
		free(str);
		return (FAILURE);
	}
	wc->flags &= ~WILDCARD_LAST;
	buff_clear(&data->buffer);
	return (SUCCESS);
}
