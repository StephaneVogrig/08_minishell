/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:16:42 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/04 11:18:02 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"

char	*new_current_cmd(t_cmd **cmd, char *str)
{
	t_cmd	*new;	

	new = cmd_new();
	if (!new)
		return (NULL);
	new->previous = *cmd;
	new->flag = PIPE;
	(*cmd)->next = new;
	*cmd = new;
	return (++str);
}
