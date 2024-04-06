/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:36:43 by stephane          #+#    #+#             */
/*   Updated: 2024/04/06 21:50:28 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_input.h"
#include "debug.h"

t_bool	is_not_valid(char *input)
{
	if (*input == '|' || *(input + ft_strlen(input) - 1) == '|')
	{
		fd_printf(STDERR_FD, "bash: syntax error near \" | \"\n");
		return (TRUE);
	}
	return (FALSE);	
}


int	exec_pipeline(t_cmd *pipeline, t_list *herdocs)
{
	// int		pipe_[2];
	// pid_t	*pids;
	// int		i;
	// int		exit_code;
	// int		nb_cmd;

	// nb_cmd = cmd_nbr(pipeline);
	// pids = pipex_malloc(sizeof(int) * nb_cmd, "pipex: main: malloc");
	// if (pipe(pipe_))
	// 	exit_pipex("pipex: process_outfile: fork", pids, NULL);
	// i = 0;

	// pids[0] = process_infile(cmd++, pipe_, envp, pids);
	// while (i < (nb_cmd - 2) && pids[i] > -1)
	// 	pids[++i] = process_pipes(cmd++, &pipe_[READ], envp, pids);
	// pids[++i] = process_outfile(cmd, &pipe_[READ], envp, pids);
	// close(pipe_[READ]);
	// exit_code = wait_process(pids, i);
	// free(pids);
	// return (exit_code);
	
	// ft_printf("start exec_pipeline\n");
	if(!pipeline)
		return (0);
	if(!herdocs)
		return (0);
	return (0);
}

void	exec_input(char *input)
{
	t_cmd	*pipeline;
	t_list	*heredocs;
	int		exit_code;
	
	if (is_not_valid(input))
		return ;
	heredocs = NULL;
	pipeline = input_to_pipeline(skip_blank(input), &heredocs);
	if (!pipeline)
	{
		free(input);
		exit(EXIT_FAILURE);
	}
print_pipeline(pipeline);
	// heredoc_fill(heredocs);
	exit_code = exec_pipeline(pipeline, heredocs);
	pipeline_free(&pipeline);
	// ft_lstclear(&heredocs, ft_lstclear);	
}
