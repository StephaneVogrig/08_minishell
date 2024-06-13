/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_pipelist_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:25:18 by stephane          #+#    #+#             */
/*   Updated: 2024/06/13 04:49:55 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_to_pipelist_bonus.h"

t_cmd	*input_to_pipelist(char *input)
{
	t_cmd	*pipelist;
	t_cmd	*current_cmd;
	t_cmd	*current_pipeline;

	pipelist = pipelist_new();
	if (!pipelist)
		return (NULL);
	current_pipeline = pipelist;
	current_cmd = pipelist->pipeline;
	while (*input)
	{
		input = parse(input, &current_cmd, &current_pipeline);
		if (!input)
		{
			pipelist_free(pipelist);
			return (NULL);
		}
		input = skip_blank(input);
	}
	return (pipelist);
}
