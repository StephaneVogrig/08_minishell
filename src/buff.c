/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 01:10:34 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/12 04:18:53 by svogrig          ###   ########.fr       */
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
		if (!buffsave_add_new(buffer->save_last))
			return (FAILURE);
	buffer->save_last->data[buffer->save_last->offset++] = c;
	return (SUCCESS);
}

t_bool	buff_add_str(t_buff *buffer, char *str)
{
	if (!str)
		return (FAILURE);
	while (*str && buffer->offset < BUFFER_SIZE)
		buffer->data[buffer->offset++] = *str++;
	if (!*str)
		return (SUCCESS);
	if (!buffer->save_last)
		if (!buff_create_save(buffer))
			return (FAILURE);
	return (buffsave_add_str(&(buffer->save_last), str));
}

int			buff_len(t_buff *buffer)
{
	int			len;
	t_buffsave	*temp;

	len = buffer->offset;
	temp = buffer->save_head;
	while (temp)
	{
		len += temp->offset;
		temp = temp->next;
	}
	return (len);
}

t_char_m	*buff_to_str(t_buff *buffer)
{
	t_char_m	*new;
	int			len;
	char		*str;
	t_buffsave	*temp;
	
	len = buff_len(buffer);
	new = malloc(sizeof(*str) * (len + 1));
	if (!new)
		return (NULL);
	ft_memcpy(new, buffer->data, buffer->offset);
	str = new + buffer->offset;
	temp = buffer->save_head;
	while (temp)
	{
		ft_memcpy(str, buffer->data, buffer->offset);
		str += temp->offset;
		temp = temp->next;
	}
	*str = '\0';
	return (new);
}
