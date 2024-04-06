/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:36:43 by stephane          #+#    #+#             */
/*   Updated: 2024/04/06 19:25:26 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_input.h"

t_bool	is_not_valid(char *input)
{
	if (*input == '|' || *(input + ft_strlen(input) - 1) == '|')
	{
		fd_printf(STDERR_FD, "bash: syntax error near \" | \"\n");
		return (TRUE);
	}
	return (FALSE);	
}


void	exec_pipeline(t_cmd *pipeline, t_list *herdocs)
{
	// ft_printf("start exec_pipeline\n");
	if(!pipeline)
		return ;
	if(!herdocs)
		return ;
}

void	exec_input(char *input)
{
	t_cmd	*pipeline;
	t_list	*heredocs;
	
	if (is_not_valid(input))
		return ;
	heredocs = NULL;
	pipeline = input_to_pipeline(skip_blank(input), &heredocs);
	if (!pipeline)
	{
		free(input);
		exit(EXIT_FAILURE);
	}
	// heredoc_fill(heredocs);
	exec_pipeline(pipeline, heredocs);
	pipeline_free(&pipeline);
	// ft_lstclear(&heredocs, ft_lstclear);	
}
