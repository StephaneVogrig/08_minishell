/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:03:55 by stephane          #+#    #+#             */
/*   Updated: 2024/06/09 23:07:05 by svogrig          ###   ########.fr       */
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
