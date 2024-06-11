/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 06:16:23 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/10 19:01:11 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char.h"

t_bool	is_meta(char c)
{
	if (ft_strchr("|<> \t", c))
		return (TRUE);
	return (FALSE);
}

t_bool	is_blank(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (TRUE);
	return (FALSE);
}

t_bool	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (TRUE);
	return (FALSE);
}

t_bool	is_special_parameter(char c)
{
	if (c == '?' || c == '-')
		return (TRUE);
	return (FALSE);
}
