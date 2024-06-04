/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_pipelist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:25:18 by stephane          #+#    #+#             */
/*   Updated: 2024/06/04 13:36:08 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_to_pipelist.h"

t_cmd	*input_to_pipelist(char *input)
{
	t_cmd	*pipeline;
	t_cmd	*cmd;

	cmd = cmd_new();
	if (!cmd)
		return (NULL);
	pipeline = cmd;
	while (*input)
	{
		input = parse(input, &cmd);
		if (!input)
		{
			pipeline_free(&pipeline);
			return (NULL);
		}
		input = skip_blank(input);
	}
	if (!cmd->next && !cmd->redir && !cmd->argv && !cmd->previous)
	{
		free(cmd);
		return (NULL);
	}
	return (pipeline);
}
