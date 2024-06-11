/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmpdata_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:08:03 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 15:12:44 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmpdata_bonus.h"

void	data_init(t_tmpdata *data)
{
	buff_init(&data->buffer);
	buff_init(&data->format);
	data->wc.list = NULL;
	data->wc.flags = 0;
}

void	data_clear(t_tmpdata *data)
{
	buff_clear(&data->buffer);
	buff_clear(&data->format);
	ft_lstclear(&data->wc.list, free);
}

t_bool	data_add_char(t_tmpdata *data, char c)
{
	if (buff_add_char(&data->buffer, c) == FAILURE)
		return (FAILURE);
	return (buff_add_char(&data->format, c));
}

t_bool	data_add_str(t_tmpdata *data, char *str)
{
	if (buff_add_str(&data->buffer, str) == FAILURE)
		return (FAILURE);
	return (buff_add_str(&data->format, str));
}

t_bool	data_add_str_n(t_tmpdata *data, char *str, int n)
{
	if (buff_add_str_n(&data->buffer, str, n) == FAILURE)
		return (FAILURE);
	return (buff_add_str_n(&data->format, str, n));
}
