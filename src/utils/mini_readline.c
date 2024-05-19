/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:50:30 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/19 16:51:07 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_readline.h"

char	*mini_readline(void)
{
	char	c;
	t_buff	buff;
	char	*str;
	int		n;

	buff_init(&buff);
	while (TRUE)
	{
		n = read(STDIN_FD, &c, 1);
		if (n < 1)
			return (NULL);
		if (c == '\n')
			break;
		if (buff_add_char(&buff, c) == FAILURE)
		{
			buff_clear(&buff);
			return (NULL);
		}
	}
	str = buff_to_str(&buff);
	buff_clear(&buff);
	return (str);
}
