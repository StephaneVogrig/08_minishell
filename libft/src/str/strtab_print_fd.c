/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtab_print_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 23:07:56 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/11 10:25:24 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	strtab_print_fd(char **tabstr, int fd)
{
	if (tabstr == NULL)
		return ;
	while (*tabstr)
	{
		ft_putstr_fd(*tabstr, fd);
		write(fd, "\n", 1);
		tabstr++;
	}
}
