/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 01:10:34 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/27 20:25:29 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "buff.h"

void	buff_init(t_buff *buffer)
{
	buffer->offset = 0;
	buffer->save_head = NULL;
	buffer->save_last = NULL;
}

void	buff_clear(t_buff *buffer)
{
	t_buffsave	*temp;
	
	while (buffer->save_head)
	{
		temp = buffer->save_head->next;
		free(buffer->save_head);
		buffer->save_head = temp;
	}
	buff_init(buffer);
}

int	buff_len(t_buff *buffer)
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
