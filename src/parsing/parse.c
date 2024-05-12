/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:21:41 by stephane          #+#    #+#             */
/*   Updated: 2024/04/29 02:03:23 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*parse_spl_quoted(t_buff *buffer, char *str)
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

char	*parse_dbl_quoted(t_buff *buffer, char *str, t_env *env, int *exit_status)
{
	str++;
	while (*str != '\"')
	{
		if (*str == '$')
		{
			str = expanse_quoted(buffer, ++str, env, exit_status);
			if (!str)
				return (NULL);
		}	
		else if (buff_add_char(buffer, *str++) == FAILURE)
			return (NULL);
	}
	str++;
	return (str);
}

char	*parse_unquoted(t_buff *buffer, char *str, t_list **argv, t_env *env)
{
	(void)argv;
	(void)env;
	if (*str == '$')
		expanse_unquoted(buffer, ++str, argv, env);
	if (buff_add_char(buffer, *str++) == FAILURE)
				return (NULL);
	return (str);
}