/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlist_print_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:02:05 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/27 20:14:03 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"

void	strlist_print_fd(t_list *strlist, int fd)
{
	if (!strlist)
		ft_putstr_fd("(empty list)\n", fd);
	while (strlist)
	{
		ft_putstr_fd(strlist->content, fd);
		ft_putchar_fd('\n', fd);
		strlist = strlist->next;
	}
}
