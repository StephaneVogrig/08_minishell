/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_new.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 00:53:31 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/08 00:59:15 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_lstadd_back_new(t_list **list, t_char_m *str)
{
	t_list *new;

	new = ft_lstnew(str);
	if (!new)
		return (FAILURE);
	ft_lstadd_back(list, new);

	return (SUCCESS);
}
