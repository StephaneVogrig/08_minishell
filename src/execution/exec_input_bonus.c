/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:57:43 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/05 17:34:42 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_input_bonus.h"

int exec_pipelist(t_cmd *pipelist, t_env **env)
{
	int		exit_code;
	t_cmd	*pipelist_head;

	exit_code = EXIT_SUCCESS;
	pipelist_head = pipelist;
	while (pipelist)
	{	
		if (pipelist->flag == AND && exit_code != EXIT_SUCCESS)
		{
			pipelist = pipelist->next;
			continue ;
		}
		if (pipelist->flag == OR && exit_code == EXIT_SUCCESS)
		{
			pipelist = pipelist->next;
			continue ;
		}
		exit_code = exec_pipeline(pipelist, env);
		pipelist = pipelist->next;
	}
	pipelist_free(pipelist_head);
	return (exit_code);
}

int	exec_input(t_char_m *input, t_env **env)
{
	t_cmd_m	*pipelist;
	char	*str;
	int		exit_code;

	str = skip_blank(input);
	if (*str == '\0')
		return (EXIT_SUCCESS);
	if (syntax_error(str))
		return (SYNTAX_ERROR);
	errno = 0;
	pipelist = input_to_pipelist(str);
	free(input);
	if (errno != 0)
		exit_on_failure(NULL, NULL, NULL, *env);
	if (!pipelist)
		return (EXIT_SUCCESS);
	exit_code = heredoc(pipelist);
	if (exit_code != SUCCESS)
		return (exit_code);
	signal(SIGINT, handler_ctrl_c);
	return (exec_pipelist(pipelist, env));
}
