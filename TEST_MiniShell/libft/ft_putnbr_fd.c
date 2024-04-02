/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:13:44 by smortemo          #+#    #+#             */
/*   Updated: 2023/11/06 14:25:12 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n >= 0 && n <= 9)
	{
		n = n + 48;
		ft_putchar_fd (n, fd);
	}
	else if (n < 0 && n != -2147483648)
	{
		n = n * (-1);
		write(fd, "-", 1);
		ft_putnbr_fd (n, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
}
