/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:36:43 by stephane          #+#    #+#             */
/*   Updated: 2024/04/07 13:42:43 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline_wait.h"
#include "exec_input.h"
#include "debug.h"
#include "process.h"

t_bool	is_not_valid(char *input)
{
	if (*input == '|' || *(input + ft_strlen(input) - 1) == '|')
	{
		fd_printf(STDERR_FD, "bash: syntax error near \" | \"\n");
		return (TRUE);
	}
	return (FALSE);	
}


int	exec_pipeline(t_cmd *cmds, t_list *heredocs, char **envp)
{
	int		pipe_[2];
	pid_t	*pids;
	int		i;
	int		exit_code;
	int		nb_cmd;
	t_cmd	*current_cmd;

	nb_cmd = cmd_nbr(cmds);
	pids = pipex_malloc(sizeof(int) * nb_cmd, "minishell: main: malloc");
	if (pipe(pipe_))
		exit_pipex("minishell: process_outfile: fork", pids, NULL);
	i = 0;
	

// print_cmd(*cmds);
	pids[0] = process_infile(cmds, pipe_, envp, pids);
	while (i < (nb_cmd - 2) && pids[i] > -1)
	{
	
		current_cmd = cmds->next;
// print_cmd(*current_cmd);
		pids[++i] = process_pipes(current_cmd, &pipe_[READ], envp, pids);
	}
	current_cmd = current_cmd->next;
// print_cmd(*current_cmd);
	pids[++i] = process_outfile(current_cmd, pipe_[READ], envp, pids);
	close(pipe_[READ]);
	exit_code = wait_process(pids, i);
	free(pids);
	return (exit_code);
	
	ft_printf("start exec_pipeline\n");
	if(!cmds || !envp || !heredocs)
		return (0);
	return (0);
}

int	exec_cmd_alone(t_cmd *cmd, char **envp)
{
	pid_t	pid[1];

	*pid = fork();
	if (*pid == 0)
	{
		exec_cmd(cmd, envp);
		exit(EXIT_FAILURE);
	}
	if (*pid == -1)
		exit (EXIT_FAILURE);
	return (wait_process(pid, 1));
}

void	exec_input(char *input, char **envp)
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
// print_pipeline(pipeline);
	// heredoc_fill(heredocs);
	if (!pipeline->next)
		exit_code = exec_cmd_alone(pipeline, envp);
	else
		exit_code = exec_pipeline(pipeline, heredocs, envp);
	pipeline_free(&pipeline);
	// ft_lstclear(&heredocs, ft_lstclear);	
}
