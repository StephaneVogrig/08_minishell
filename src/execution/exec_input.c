/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:36:43 by stephane          #+#    #+#             */
/*   Updated: 2024/06/06 21:44:39 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_input.h"

int	exec_input(t_char_m *input, t_env **env)
{
	t_cmd_m	*pipeline;
	char	*str;
	int		exit_code;

	str = skip_blank(input);
	if (*str == '\0')
		return (EXIT_SUCCESS);
	if (syntax_error(str))
		return (SYNTAX_ERROR);
	errno = 0;
	pipeline = input_to_pipeline(str);
	free(input);
	if (errno != 0)
		exit_on_failure(NULL, NULL, NULL, *env);
	if (!pipeline)
		return (EXIT_SUCCESS);
	exit_code = heredoc(pipeline);
	if (exit_code != SUCCESS)
		return (exit_code);
	signal(SIGINT, handler_ctrl_c);
	return (exec_pipeline(pipeline, env));
}
