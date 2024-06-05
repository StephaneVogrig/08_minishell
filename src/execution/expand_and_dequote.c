/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_dequote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:14:35 by stephane          #+#    #+#             */
/*   Updated: 2024/06/05 13:58:41 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_and_dequote.h"

static char	*expand_spl_quoted(t_buff *buffer, char *str)
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

static char	*expand_dbl_quoted(t_buff *buffer, char *str, t_env *env)
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

static t_bool	is_token_empty(char *str, t_env *env)
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
