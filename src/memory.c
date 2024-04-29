/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:17:10 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/29 16:32:30 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*mem_calloc(size_t nb_mem_block, size_t size)
{
	void	*new;

	new = ft_calloc(nb_mem_block, size);
	if (!new)
	{
		perror("minishell: mem_calloc");
		return (NULL);
	}
	return (new);
}
