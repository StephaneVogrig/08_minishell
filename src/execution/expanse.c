/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:03:55 by stephane          #+#    #+#             */
/*   Updated: 2024/06/10 01:33:44 by svogrig          ###   ########.fr       */
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
