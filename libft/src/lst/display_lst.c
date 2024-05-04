/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:18:00 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/03 22:44:31 by smortemo         ###   ########.fr       */
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

