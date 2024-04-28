/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffsave.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 03:35:17 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/27 10:16:30 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "buffsave.h"


t_buffsave	*buffsave_new(void)
{
	t_buffsave *new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->offset = 0;
	new->next = NULL;
	return (new);
}

t_bool	buffsave_add_new(t_buffsave **save)
{
	(*save)->next  = buffsave_new();
	if (!(*save)->next )
		return (FAILURE);
	*save = (*save)->next ;
	return (SUCCESS);
}

t_bool	buffsave_add_str(t_buffsave **save, char *str)
{
	if ((*save)->offset == BUFFER_SIZE)
		if (!buffsave_add_new(save))
			return (FAILURE);
	while (*str && (*save)->offset < BUFFER_SIZE)
		(*save)->data[(*save)->offset++] = *str++;
	if (*str)
		return (buffsave_add_str(save, str));
	return (SUCCESS);
}

t_bool	buffsave_add_str_n(t_buffsave **save, char *str, int n)
{
	if ((*save)->offset == BUFFER_SIZE)
		if (!buffsave_add_new(save))
			return (FAILURE);
	while (*str && (*save)->offset < BUFFER_SIZE && n--)
		(*save)->data[(*save)->offset++] = *str++;
	if (*str || n > 0)
		return (buffsave_add_str_n(save, str, n));
	return (SUCCESS);
}
