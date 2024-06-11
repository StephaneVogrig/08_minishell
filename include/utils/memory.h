/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:18:18 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 14:56:31 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "libft.h"

void	*mem_calloc(size_t nb_mem_block, size_t size);
void	*mem_malloc(size_t size);

#endif
