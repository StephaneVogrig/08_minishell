/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtab_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 23:16:47 by stephane          #+#    #+#             */
/*   Updated: 2024/06/19 22:34:22 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	strtab_free(char **strtab)
{
	char	**current;

	if (strtab == NULL)
		return ;
	current = strtab;
	while (*current)
		free(*current++);
	free(strtab);
}

int	ft_strtab_size(char **strtab)
{
	int	i;

	if (!strtab)
		return (0);
	i = 0;
	while (*strtab++)
		i++;
	return (i);
}
