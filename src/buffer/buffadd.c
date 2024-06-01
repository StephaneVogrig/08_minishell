/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffadd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 03:46:40 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/31 15:55:37 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buff.h"

t_bool	buff_create_save(t_buff *buffer)
{
	buffer->save_head = buffsave_new();
	if (!buffer->save_head)
		return (FAILURE);
	buffer->save_last = buffer->save_head;
	return (SUCCESS);
}

t_bool	buff_add_char(t_buff *buffer, char c)
{
	if (buffer->offset < BUFFER_SIZE)
	{
		buffer->data[buffer->offset++] = c;
		return (SUCCESS);
	}
	if (!buffer->save_last)
		if (!buff_create_save(buffer))
			return (FAILURE);
	if (buffer->save_last->offset == BUFFER_SIZE)
		if (!buffsave_add_new(&(buffer->save_last)))
			return (FAILURE);
	buffer->save_last->data[buffer->save_last->offset++] = c;
	return (SUCCESS);
}

t_bool	buff_add_str(t_buff *buffer, char *str)
{
	if (!str)
		return (SUCCESS);
	while (*str && buffer->offset < BUFFER_SIZE)
		buffer->data[buffer->offset++] = *str++;
	if (!*str)
		return (SUCCESS);
	if (!buffer->save_last)
		if (!buff_create_save(buffer))
			return (FAILURE);
	return (buffsave_add_str(&(buffer->save_last), str));
}

t_bool	buff_add_str_n(t_buff *buffer, char *str, int n)
{
	if (!str || n < 1)
		return (SUCCESS);
	while (*str && buffer->offset < BUFFER_SIZE && n--)
		buffer->data[buffer->offset++] = *str++;
	if (!*str || n < 1)
		return (SUCCESS);
	if (!buffer->save_last)
		if (!buff_create_save(buffer))
			return (FAILURE);
	return (buffsave_add_str_n(&(buffer->save_last), str, n));
}
