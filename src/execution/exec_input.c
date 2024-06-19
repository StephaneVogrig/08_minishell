/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:36:43 by stephane          #+#    #+#             */
/*   Updated: 2024/06/19 20:46:08 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_input.h"

int	exec_input(t_char_m *input, t_env **env)
{
	t_cmd_m	*pipeline;
	char	*str;
	int		exit_code;

	str = skip_blank(input);
	if (syntax_error(str))
		return (SYNTAX_ERROR);
	pipeline = input_to_pipeline(str);
	free(input);
	if (!pipeline)
		return (EXIT_FAILURE);
	exit_code = heredoc(pipeline, *env);
	if (exit_code != EXIT_SUCCESS)
	{
		pipeline_free(&pipeline);
		return (exit_code);
	}
	signal(SIGINT, handler_ctrl_c);
	exit_code = exec_pipeline(pipeline, env, pipeline);
	pipeline_free(&pipeline);
	return (exit_code);
}
