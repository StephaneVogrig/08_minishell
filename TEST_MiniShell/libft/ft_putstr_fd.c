/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:42:27 by smortemo          #+#    #+#             */
/*   Updated: 2024/03/19 15:59:50 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_putstr_fd(char *s, int fd)
{
	int	count;
	int	i;

	if (!s)
		return (0);
	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		count++;
		i++;
	}
	return (count);
}
