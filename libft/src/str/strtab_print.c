/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtab_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 23:05:59 by stephane          #+#    #+#             */
/*   Updated: 2024/04/10 21:48:18 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	strtab_print(char **tabstr)
{
	if (tabstr == NULL)
		return ;
	while (*tabstr)
	{
		ft_putstr_fd(*tabstr, STDOUT_FD);
		write(STDOUT_FD, '\n', 1);
		tabstr++;
	}
}
