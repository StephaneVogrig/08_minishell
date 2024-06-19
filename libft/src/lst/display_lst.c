/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:18:00 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/19 22:33:30 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	display_lst(t_list *lst)
{
	while (lst != NULL)
	{
		ft_printf("-> %s \n", lst->content);
		lst = lst->next;
	}
}
