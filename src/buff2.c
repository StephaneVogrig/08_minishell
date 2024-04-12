/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 03:46:40 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/12 03:47:29 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
