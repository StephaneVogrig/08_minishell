/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: smortemo <marvin@42.fr>                    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/02/11 16:08:32 by smortemo          #+#    #+#             */
/*   Updated: 2024/02/11 16:08:36 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_print_unsigned(unsigned long nbr, int base)
{
	unsigned int	count;

	count = 0;
	if (nbr < 10)
		count = count + ft_print_char(nbr + 48);
	else if (base == 16 && (nbr < 16 && nbr >= 0))
		count = count + ft_print_char(nbr + 87);
	else
	{
		count = ft_print_unsigned(nbr / base, base);
		count = count + ft_print_unsigned(nbr % base, base);
	}
	return (count);
}

static unsigned int	ft_print_pointer(unsigned long *pointer)
{
	unsigned int	count;
	unsigned long	nbr;

	count = 0;
	if (pointer == NULL)
	{
		count = count + write(1, "(nil)", 5);
		return (count);
	}
	count = count + write(1, "0x", 2);
	nbr = (unsigned long)pointer;
	count = count + ft_print_unsigned(nbr, 16);
	return (count);
}

static unsigned int	print_type(va_list ap, char type_to_print)
{
	unsigned int	counter;

	counter = 0;
	if (type_to_print == '\0')
		counter = -1;
	if (type_to_print == '%')
		counter = counter + write(1, "%", 1);
	if (type_to_print == 'c')
		counter = counter + ft_print_char(va_arg(ap, int));
	if (type_to_print == 's')
		counter = counter + ft_putstr(va_arg(ap, char *));
	if (type_to_print == 'p')
		counter = counter + ft_print_pointer(va_arg(ap, unsigned long *));
	if (type_to_print == 'd')
		counter = counter + ft_print_nbr_base(va_arg(ap, int), 10, 'x');
	if (type_to_print == 'i')
		counter = counter + ft_print_nbr_base(va_arg(ap, int), 10, 'x');
	if (type_to_print == 'u')
		counter = counter + ft_print_unsigned(va_arg(ap, unsigned int), 10);
	if (type_to_print == 'x')
		counter += ft_print_nbr_base(va_arg(ap, unsigned int), 16, 'x');
	if (type_to_print == 'X')
		counter += ft_print_nbr_base(va_arg(ap, unsigned int), 16, 'X');
	return (counter);
}

static unsigned int	percent(const char *format, va_list ap)
{
	unsigned int	counter;
	unsigned int	flag;
	unsigned int	i;

	flag = 0;
	counter = 0;
	i = -1;
	while (format[++i] != '\0')
	{
		if (format[i] == '%' && ft_strchr("cspdiuxX%", format[i + 1]) != NULL
			&& format[i + 1] != '\0')
			counter = counter + print_type(ap, format[i++ + 1]);
		else if (format[i] == '%' && format[i + 1] != '\0')
		{
			counter = counter + write(1, "%", 1);
			flag = 1;
		}
		else if (format[i] == '%' && format[i + 1] == '\0' && flag == 0)
			return (-1);
		else
			counter = counter + write(1, &format[i], 1);
	}
	return (counter);
}

int	ft_printf(const char *format, ...)
{
	va_list			ap;
	unsigned int	counter;
	unsigned int	i;

	i = 0;
	counter = 0;
	va_start(ap, format);
	if (format == NULL)
		return (-1);
	if (format[i] != '\0')
		counter += percent(format, ap);
	va_end(ap);
	return (counter);
}
