/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:36:43 by stephane          #+#    #+#             */
/*   Updated: 2024/06/05 17:44:58 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_input.h"

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
	return (exec_pipeline(pipelist, env));
}
