/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:43:15 by smortemo          #+#    #+#             */
/*   Updated: 2023/11/17 14:22:31 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		len_of_int(int n);
static	char		*int_to_char(int len, char *nb, long long nbr);
char			*ft_itoa(int n);

char	*ft_itoa(int n)
{
	char		*nb;
	long long	nbr;
	int			len;
	char		*min;

	min = "-2147483648";
	nbr = (long long)n;
	len = 0;
	if (n == -2147483648)
	{
		nb = ft_strdup(min);
		return (nb);
	}
	len = len_of_int(n);
	nb = (char *) malloc(sizeof(char) * (len + 1));
	if (!nb)
		return (NULL);
	nb = int_to_char(len, nb, nbr);
	return (nb);
}

static	char	*int_to_char(int len, char *nb, long long nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		nb[0] = 48;
	i = len - 1;
	if (nbr < 0)
	{
		nb[0] = '-';
		nbr = -nbr;
	}
	if (nbr > 0)
	{
		while (nbr != 0)
		{
			nb[i] = nbr % 10 + 48;
			nbr = nbr / 10;
			i--;
		}
	}
	nb[len] = '\0';
	return (nb);
}

static	int	len_of_int(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len = 1;
	if (n < 0)
	{
		n = -n;
		len = 1;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}
