/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:17:10 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/31 15:53:22 by smortemo         ###   ########.fr       */
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

void	*mem_malloc(size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
	{
		perror("minishell: mem_malloc");
		return (NULL);
	}
	return (new);
}
