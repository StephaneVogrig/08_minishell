/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 05:44:26 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/04 05:53:22 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv.h"

t_bool	argv_add_buffer(t_list **argv, t_buff *buffer)
{
	t_char_m	*token;

	token = buff_to_str(buffer);
	buff_clear(buffer);
	if(!token)
		return (FAILURE);
	return (add_to_strlist(argv, token));
}
