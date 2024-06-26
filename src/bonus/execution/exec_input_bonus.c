/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:57:43 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/19 22:02:56 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_input_bonus.h"

void	pipelist_redir_unlink(t_cmd *pipelist)
{
	while (pipelist)
	{
		pipeline_redir_unlink(pipelist->pipeline);
		pipelist = pipelist->next;
	}
}

int	exec_input(t_char_m *input, t_env **env)
{
	t_cmd_m	*pipelist;
	char	*str;
	int		exit_code;

	str = skip_blank(input);
	if (syntax_error(str))
		return (SYNTAX_ERROR);
	pipelist = input_to_pipelist(str);
	free(input);
	if (!pipelist)
		return (EXIT_SUCCESS);
	exit_code = heredoc(pipelist, *env);
	if (exit_code != EXIT_SUCCESS)
	{
		pipelist_free(pipelist);
		return (exit_code);
	}
	signal(SIGINT, handler_ctrl_c);
	exit_code = exec_pipelist(pipelist, env, pipelist);
	pipelist_redir_unlink(pipelist);
	pipelist_free(pipelist);
	return (exit_code);
}
