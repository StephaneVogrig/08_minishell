/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: smortemo <marvin@42.fr>                    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/02/11 16:08:53 by smortemo          #+#    #+#             */
/*   Updated: 2024/02/11 16:34:31 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str)
{
	unsigned int	count;
	unsigned int	i;

	count = 0;
	i = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (i + 6);
	}
	while (str[i] != '\0')
	{
		count = count + write(1, &str[i], 1);
		i++;
	}
	return (count);
}
