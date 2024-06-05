/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelist_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:14:41 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/04 20:59:20 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipelist_bonus.h"

void	pipelist_free(t_cmd *pipelist)
{
	t_cmd	*temp;

	while (pipelist->previous)
		pipelist = pipelist->previous;
	
	while (pipelist)
	{
		pipeline_free(&pipelist->pipeline);
		temp = pipelist->next;
		free(pipelist);
		pipelist = temp;
	}
}