/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_dequote_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 23:18:52 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/10 02:51:18 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_and_dequote_bonus.h"

t_bool	split_word(char *str, t_tmpdata *data, t_list **argv)
{
	while (*str)
	{
		if (is_blank(*str))
		{
			if (strlist_add_buffer(argv, &data->buffer) == FAILURE)
				return (FAILURE);
			data_clear(data);
			while (is_blank(*str))
				str++;
		}
		while (*str && !is_blank(*str))
		{
			if (data_add_char(data, *str) == FAILURE)
				return (FAILURE);
			str++;
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
	ft_printf("str = %s\n", str);
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
		else if (data_add_char(&data, *str++) == FAILURE)
			str = NULL;
	}
	if (str && strlist_add_buffer(strlist, &data.buffer) == FAILURE)
		str = NULL;
	data_clear(&data);
	if (str)
		return (SUCCESS);
	ft_lstclear(strlist, free);
	return (FAILURE);
}

// t_bool	expand_and_dequote(char *str, t_list **strlist, t_env *env)
// {
// 	t_buff		buffer;
// 	t_wildcard	*wc;

// 	if (is_token_empty(str, env))
// 		return (SUCCESS);
// 	wc = NULL;
// 	buff_init(&buffer);
// 	buff_init(&buffersave);
// 	while (str && *str)
// 	{
// 		if (*str == '\'')
// 			str = expand_spl_quoted(&buffer, str);
// 		else if (*str == '\"')
// 			str = expand_dbl_quoted(&buffer, str, env);
// 		else if (*str == '$')
// 			str = expanse_unquoted(&buffer, str, strlist, env);
// 		else if (*str == '*')
// 			str = handle_wildcard(&buffer, str);
// 		else if (buff_add_char(&buffer, *str++) == FAILURE)
// 			str = NULL;
// 	}
// 	if (str)
// 	{
// 		if (!wc && strlist_add_buffer(strlist, &buffer) == FAILURE)
// 			str = NULL;
		
// 	}
// 	buff_clear(&buffer);
// 	buff_clear(&buffersave);
// 	if (str)
// 		return (SUCCESS);
// 	ft_lstclear(strlist, free);
// 	return (FAILURE);
// }
