/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:35:15 by smortemo          #+#    #+#             */
/*   Updated: 2024/03/19 15:34:02 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_nbr_base(long long nbr, int base, char up)
{
	unsigned int	count;

	count = 0;
	if (nbr < 0)
	{
		write(1, "-", 1);
		count = count + 1;
		nbr = -nbr;
	}
	if (nbr < 10)
		count = count + ft_print_char(nbr + 48);
	else if (up == 'x' && base == 16 && (nbr < 16 && nbr >= 0))
		count = count + ft_print_char(nbr + 87);
	else if (up == 'X' && base == 16 && (nbr < 16 && nbr >= 0))
		count = count + ft_print_char(nbr + 55);
	else
	{
		count = count + ft_print_nbr_base(nbr / base, base, up);
		count = count + ft_print_nbr_base(nbr % base, base, up);
	}
	return (count);
}
