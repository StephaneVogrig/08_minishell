/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:52:25 by svogrig           #+#    #+#             */
/*   Updated: 2024/02/22 19:24:00 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	while (n > 8)
	{
		*(t_ui64 *)s = 0;
		s += 8;
		n -= 8;
	}
	while (n)
	{
		*(t_ui8 *)s = 0;
		s++;
		n--;
	}
}