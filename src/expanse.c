/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:03:55 by stephane          #+#    #+#             */
/*   Updated: 2024/04/29 06:22:24 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanse.h"

char	*end_name(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (NULL);
	str++;
	while (ft_isalnum(*str) || *str == '_')
		str++;
	return (str);
}

char	*expanse_exit_status(t_buff *buffer, char *str, int *exit_status)
{
	t_char_m	*nbrstr;
	
	nbrstr = ft_itoa(*exit_status);
	if (!nbrstr)
		return (NULL);
	if (buff_add_str(buffer, nbrstr) == FAILURE)
		return (NULL);
	free(nbrstr);
	return (++str);		
}

char	*expanse_quoted(t_buff *buffer, char *str, t_env *env, int *exit_status)
{
	char	*end;
	
	if (*str == '?')
		return (expanse_exit_status(buffer, str, exit_status));
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
// ft_printf("split_word:\"%s\"\n", str);
// strlist_print_fd(*argv, 1);
	while (*str)
	{
		if (is_blank(*str))
		{
			if (argv_add_buffer(argv, buffer) == FAILURE)
				return (FAILURE);
// ft_printf("is blank:\"%s\"\n", str);
// strlist_print_fd(*argv, 1);
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
	(void)argv;
	char	*end;
	
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
