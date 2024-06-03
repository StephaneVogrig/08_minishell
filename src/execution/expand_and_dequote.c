/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_dequote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:14:35 by stephane          #+#    #+#             */
/*   Updated: 2024/06/03 16:30:56 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_and_dequote.h"

static t_bool	is_token_empty(char *str, t_env *env)
{
	char	*end;

	if (*str != '$')
		return (FALSE);
	while (*str && !is_meta(*str))
	{
		if (*str == '$')
		{
			end = end_name(++str);
			if (end == str)
				return (FALSE);
			if (env_get_n(env, str, end - str))
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
			str = parse_spl_quoted(&buffer, str);
		else if (*str == '\"')
			str = parse_dbl_quoted(&buffer, str, env);
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
